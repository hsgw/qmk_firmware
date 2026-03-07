// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lp5868.h"
#include "config.h"
#include "quantum.h"
#include "spi_master.h"
#include <string.h>
#include <hal.h>

// Frame buffer for 16x8 matrix
static uint8_t lp5868_buffer[LED_MATRIX_ROWS][LP5868_DRIVER_WIDTH];

// DMA buffer: 2 bytes header + LED data
static uint8_t lp5868_dma_buffer[2 + LP5868_BYTES_PER_DRIVER];

typedef enum {
    LP5868_IDLE,
    LP5868_TRANSFERRING,
    LP5868_VSYNC_PULSE
} lp5868_state_t;

static lp5868_state_t lp5868_state      = LP5868_IDLE;
static uint32_t       vsync_start_time = 0;

static void create_spi_header(uint16_t address, bool is_write, uint8_t* out_bytes) {
    out_bytes[0] = (address >> 2) & 0xFF;
    out_bytes[1] = (address & 0x03) << 6;
    if (is_write) {
        out_bytes[1] |= 0x20;
    }
}

void lp5868_write_reg(uint16_t reg, uint8_t data) {
    uint8_t header[2];
    create_spi_header(reg, true, header);

    if (spi_start(LP5868_CS_PIN, false, 0, 32)) {
        spi_transmit(header, 2);
        spi_write(data);
        spi_stop();
    }
}

void lp5868_write_buffer(uint16_t reg, const uint8_t* data, uint16_t len) {
    uint8_t header[2];
    create_spi_header(reg, true, header);

    if (spi_start(LP5868_CS_PIN, false, 0, 32)) {
        spi_transmit(header, 2);
        spi_transmit(data, len);
        spi_stop();
    }
}

void lp5868_init(void) {
    spi_init();

    // VSYNC pin initialization
    gpio_set_pin_output_push_pull(LP5868_VSYNC_PIN);
    gpio_write_pin_low(LP5868_VSYNC_PIN);

    // CS pin initialization
    gpio_set_pin_output_push_pull(LP5868_CS_PIN);
    gpio_write_pin_high(LP5868_CS_PIN);

    memset(lp5868_buffer, 0, sizeof(lp5868_buffer));
    lp5868_state = LP5868_IDLE;

    // Initialization Sequence
    lp5868_write_reg(REG_SW_RESET, 0xFF);
    wait_ms(10);

    lp5868_write_reg(REG_CHIP_EN, 0x01);
    wait_ms(10);

    lp5868_write_reg(REG_DEV_INITIAL, 0x42);
    lp5868_write_reg(REG_DEV_CONFIG1, 0x04);
    lp5868_write_reg(REG_DEV_CONFIG3, 0x49);

    uint8_t rgb_current[3] = {0x7F, 0x7F, 0x7F};
    lp5868_write_buffer(REG_RGB_CURRENT, rgb_current, 3);

    uint8_t fill_ff[LP5868_BYTES_PER_DRIVER];
    memset(fill_ff, 0xFF, sizeof(fill_ff));
    lp5868_write_reg(REG_GLOBAL_BRI, 0xFF);
    lp5868_write_buffer(REG_DOT_CURRENT_BASE, fill_ff, LP5868_BYTES_PER_DRIVER);

    wait_ms(10);
    lp5868_write_reg(REG_CHIP_EN, 0x00);
    wait_ms(10);
    lp5868_write_reg(REG_CHIP_EN, 0x01);
    wait_ms(10);

    lp5868_fill_pixel(0);
    // Initial update is blocking to ensure clean start
    lp5868_write_buffer(REG_PWM_BRI_BASE, &lp5868_buffer[0][0], LP5868_BYTES_PER_DRIVER);
}

void lp5868_set_pixel(uint8_t x, uint8_t y, uint8_t brightness) {
    if (x >= LED_MATRIX_COLS || y >= LED_MATRIX_ROWS) return;
    lp5868_buffer[y][x] = brightness;
}

void lp5868_fill_pixel(uint8_t brightness) {
    memset(lp5868_buffer, brightness, sizeof(lp5868_buffer));
}

void lp5868_update(void) {
    if (lp5868_state != LP5868_IDLE) return;

    // Prepare DMA buffer: Header + Data
    lp5868_dma_buffer[0] = (REG_PWM_BRI_BASE >> 2) & 0xFF;
    lp5868_dma_buffer[1] = ((REG_PWM_BRI_BASE & 0x03) << 6) | 0x20;
    memcpy(&lp5868_dma_buffer[2], lp5868_buffer, LP5868_BYTES_PER_DRIVER);

    // Start Async Transfer using ChibiOS HAL directly for DMA
    if (spi_start(LP5868_CS_PIN, false, 0, 32)) {
        // Bypass spi_transmit and use spiStartSend for DMA
        spiStartSend(&SPI_DRIVER, sizeof(lp5868_dma_buffer), lp5868_dma_buffer);
        lp5868_state = LP5868_TRANSFERRING;
    }
}

/**
 * @brief Handle background tasks for the LP5868 driver.
 *
 * This function manages the asynchronous DMA transfer state machine and VSYNC pulse timing.
 * It should be called frequently from housekeeping_task_kb() to ensure smooth operation
 * without blocking the main keyboard loop.
 */
void lp5868_task(void) {
    switch (lp5868_state) {
        case LP5868_TRANSFERRING:
            // Check if DMA transfer is complete
            if (SPI_DRIVER.state == SPI_READY) {
                spi_stop(); // Release CS and Bus using QMK abstraction
                gpio_write_pin_high(LP5868_VSYNC_PIN);
                vsync_start_time = timer_read32();
                lp5868_state     = LP5868_VSYNC_PULSE;
            }
            break;

        case LP5868_VSYNC_PULSE:
            // Wait for 1ms (original was 250us, 1ms is safe and fits timer_read32)
            if (timer_elapsed32(vsync_start_time) >= 1) {
                gpio_write_pin_low(LP5868_VSYNC_PIN);
                lp5868_state = LP5868_IDLE;
            }
            break;

        default:
            break;
    }
}
