// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lp5868-mono.h"
#include "config.h"
#include "quantum.h"
#include "spi_master.h"
#include "led_matrix.h"
#include <string.h>
#include <hal.h>

// LP5868 Register Definitions
#define REG_CHIP_EN 0x000
#define REG_DEV_INITIAL 0x001
#define REG_DEV_CONFIG1 0x002
#define REG_DEV_CONFIG2 0x003
#define REG_DEV_CONFIG3 0x004
#define REG_GLOBAL_BRI 0x005
#define REG_RGB_CURRENT 0x009
#define REG_SW_RESET 0x0A9
#define REG_DOT_CURRENT_BASE 0x100
#define REG_PWM_BRI_BASE 0x200

#define LP5868_DRIVER_WIDTH 18
#define LP5868_DRIVER_HEIGHT 8
#define LP5868_BYTES_PER_DRIVER (LP5868_DRIVER_WIDTH * LP5868_DRIVER_HEIGHT)

// CS pins for all LP5868 drivers
static const pin_t lp5868_cs_pins[] = LP5868_CS_PINS;

// Frame buffer for the entire matrix
static uint8_t lp5868_buffer[LED_MATRIX_ROWS][LP5868_DRIVER_WIDTH];

// DMA buffer: 2 bytes header + LED data for one driver
static uint8_t lp5868_dma_buffer[2 + LP5868_BYTES_PER_DRIVER];

typedef enum { LP5868_IDLE, LP5868_TRANSFERRING, LP5868_VSYNC_PULSE } lp5868_state_t;

static lp5868_state_t lp5868_state            = LP5868_IDLE;
static uint8_t        lp5868_current_driver   = 0;
static uint32_t       lp5868_vsync_start_time = 0;
static bool           lp5868_update_pending   = false;

static void create_spi_header(uint16_t address, bool is_write, uint8_t* out_bytes) {
    out_bytes[0] = (address >> 2) & 0xFF;
    out_bytes[1] = (address & 0x03) << 6;
    if (is_write) {
        out_bytes[1] |= 0x20;
    }
}

// Blocking write to a specific chip select
static void lp5868_write_reg_to(pin_t cs_pin, uint16_t reg, uint8_t data) {
    uint8_t header[2];
    create_spi_header(reg, true, header);

    if (spi_start(cs_pin, false, 0, 32)) {
        spi_transmit(header, 2);
        spi_write(data);
        spi_stop();
    }
}

static void lp5868_write_buffer_to(pin_t cs_pin, uint16_t reg, const uint8_t* data, uint16_t len) {
    uint8_t header[2];
    create_spi_header(reg, true, header);

    if (spi_start(cs_pin, false, 0, 32)) {
        spi_transmit(header, 2);
        spi_transmit(data, len);
        spi_stop();
    }
}

void lp5868_init(void) {
    spi_init();

    // VSYNC pin initialization (shared)
    gpio_set_pin_output_push_pull(LP5868_VSYNC_PIN);
    gpio_write_pin_low(LP5868_VSYNC_PIN);

    // CS pins initialization
    for (int i = 0; i < LP5868_DRIVER_COUNT; i++) {
        gpio_set_pin_output_push_pull(lp5868_cs_pins[i]);
        gpio_write_pin_high(lp5868_cs_pins[i]);
    }

    memset(lp5868_buffer, 0, sizeof(lp5868_buffer));
    lp5868_state          = LP5868_IDLE;
    lp5868_update_pending = false;

    // Initialization Sequence for all chips
    for (int i = 0; i < LP5868_DRIVER_COUNT; i++) {
        pin_t cs = lp5868_cs_pins[i];
        lp5868_write_reg_to(cs, REG_SW_RESET, 0xFF);
        wait_ms(10);
        lp5868_write_reg_to(cs, REG_CHIP_EN, 0x01);
        wait_ms(10);
        lp5868_write_reg_to(cs, REG_DEV_INITIAL, 0x42);
        lp5868_write_reg_to(cs, REG_DEV_CONFIG1, 0x04);
        lp5868_write_reg_to(cs, REG_DEV_CONFIG3, 0x49);

        uint8_t rgb_current[3] = {0x7F, 0x7F, 0x7F};
        lp5868_write_buffer_to(cs, REG_RGB_CURRENT, rgb_current, 3);

        uint8_t fill_ff[LP5868_BYTES_PER_DRIVER];
        memset(fill_ff, 0xFF, sizeof(fill_ff));
        lp5868_write_reg_to(cs, REG_GLOBAL_BRI, 0xFF);
        lp5868_write_buffer_to(cs, REG_DOT_CURRENT_BASE, fill_ff, LP5868_BYTES_PER_DRIVER);

        wait_ms(10);
        lp5868_write_reg_to(cs, REG_CHIP_EN, 0x00);
        wait_ms(10);
        lp5868_write_reg_to(cs, REG_CHIP_EN, 0x01);
        wait_ms(10);
    }

    memset(lp5868_buffer, 0, sizeof(lp5868_buffer));
}

void lp5868_set_value(int index, uint8_t value) {
    if (index < 0 || index >= LED_MATRIX_LED_COUNT) return;
    uint8_t row = (uint8_t)index / LED_MATRIX_COLS;
    uint8_t col = (uint8_t)index % LED_MATRIX_COLS;
    if (col >= LP5868_DRIVER_WIDTH || row >= LED_MATRIX_ROWS) return;
    lp5868_buffer[row][col] = value;
}

void lp5868_set_value_all(uint8_t value) {
    memset(lp5868_buffer, value, sizeof(lp5868_buffer));
}

static bool lp5868_start_transfer(uint8_t driver_index) {
    uint8_t start_row = driver_index * LP5868_DRIVER_HEIGHT;
    if (start_row >= LED_MATRIX_ROWS) return false;

    // Create SPI header for PWM brightness register base
    create_spi_header(REG_PWM_BRI_BASE, true, &lp5868_dma_buffer[0]);

    // Data: 8 rows * 18 bytes
    memcpy(&lp5868_dma_buffer[2], &lp5868_buffer[start_row][0], LP5868_BYTES_PER_DRIVER);

    if (spi_start(lp5868_cs_pins[driver_index], false, 0, 32)) {
        spiStartSend(&SPI_DRIVER, sizeof(lp5868_dma_buffer), lp5868_dma_buffer);
        return true;
    }
    return false;
}

void lp5868_flush(void) {
    // 1. Mark that a new frame is ready to be sent.
    // The actual transfer sequence will be initiated in lp5868_task() when the driver is IDLE.
    lp5868_update_pending = true;
}

/**
 * @brief Handle background tasks for the LP5868 driver.
 *
 * This function manages the asynchronous DMA transfer state machine:
 * 1. If IDLE and update is pending, start transfer for the first driver.
 * 2. While TRANSFERRING, wait for the current DMA to finish, then start the next driver.
 * 3. After all drivers are sent, generate a VSYNC pulse to latch the data into the chips.
 */
void lp5868_task(void) {
    switch (lp5868_state) {
        case LP5868_IDLE:
            // Check if there is a pending request to update the LEDs
            if (lp5868_update_pending) {
                lp5868_update_pending = false;
                lp5868_current_driver = 0;
                if (lp5868_start_transfer(lp5868_current_driver)) {
                    lp5868_state = LP5868_TRANSFERRING;
                }
            }
            break;

        case LP5868_TRANSFERRING:
            // Check if the current DMA transfer is complete
            if (SPI_DRIVER.state == SPI_READY) {
                spi_stop(); // Releases the CS pin for the current driver

                lp5868_current_driver++;
                if (lp5868_current_driver < LP5868_DRIVER_COUNT) {
                    // Start transfer for the next driver
                    if (!lp5868_start_transfer(lp5868_current_driver)) {
                        goto start_vsync;
                    }
                } else {
                start_vsync:
                    // All data has been sent to all drivers.
                    // Generate a VSYNC pulse (high) to latch the PWM data.
                    gpio_write_pin_high(LP5868_VSYNC_PIN);
                    lp5868_vsync_start_time = timer_read32();
                    lp5868_state            = LP5868_VSYNC_PULSE;
                }
            }
            break;

        case LP5868_VSYNC_PULSE:
            // VSYNC pulse should be high for at least 250us.
            // Using 1ms here for safety and reliable tracking with timer_read32.
            if (timer_elapsed32(lp5868_vsync_start_time) >= 1) {
                gpio_write_pin_low(LP5868_VSYNC_PIN);
                lp5868_state = LP5868_IDLE;
            }
            break;

        default:
            break;
    }
}
