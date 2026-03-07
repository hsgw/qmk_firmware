// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lp5868.h"
#include "config.h"
#include "quantum.h"
#include "led_matrix.h"
#include "spi_master.h"
#include "platforms/gpio.h"
#include "deferred_exec.h"
#include <string.h>

// Frame buffer for 16x8 matrix (16 columns used out of 18 available in the driver)
static uint8_t lp5868_buffer[LED_MATRIX_ROWS][LP5868_DRIVER_WIDTH];

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

    if (spi_start(LP5868_CS_PIN, false, 0, 32)) { // RP2040 uses divisor, 32 for ~4MHz if CPU is 125MHz
        spi_write(header[0]);
        spi_write(header[1]);
        spi_write(data);
        spi_stop();
    }
}

void lp5868_write_buffer(uint16_t reg, const uint8_t* data, uint16_t len) {
    uint8_t header[2];
    create_spi_header(reg, true, header);

    if (spi_start(LP5868_CS_PIN, false, 0, 32)) {
        spi_write(header[0]);
        spi_write(header[1]);
        spi_transmit(data, len);
        spi_stop();
    }
}

void lp5868_init(void) {
    spi_init();

    // VSYNC pin initialization
    gpio_set_pin_output_push_pull(LP5868_VSYNC_PIN);
    gpio_write_pin_low(LP5868_VSYNC_PIN);

    // CS pin initialization (handled by spi_start, but ensuring high initially)
    gpio_set_pin_output_push_pull(LP5868_CS_PIN);
    gpio_write_pin_high(LP5868_CS_PIN);

    memset(lp5868_buffer, 0, sizeof(lp5868_buffer));

    // Initialization Sequence
    // Software Reset
    lp5868_write_reg(REG_SW_RESET, 0xFF);
    wait_ms(10);

    // Enable Chip
    lp5868_write_reg(REG_CHIP_EN, 0x01);
    wait_ms(10);

    // Initialize: mode 2 (8bits, use vsync), exp scale
    lp5868_write_reg(REG_DEV_INITIAL, 0x42);
    lp5868_write_reg(REG_DEV_CONFIG1, 0x04);
    lp5868_write_reg(REG_DEV_CONFIG3, 0x49);

    // RGB Current Setting
    uint8_t rgb_current[3] = {0x7F, 0x7F, 0x7F};
    lp5868_write_buffer(REG_RGB_CURRENT, rgb_current, 3);

    // Dot Current (DC) initialization buffer (all 0xFF)
    uint8_t fill_ff[LP5868_BYTES_PER_DRIVER];
    memset(fill_ff, 0xFF, sizeof(fill_ff));
    lp5868_write_reg(REG_GLOBAL_BRI, 0xFF);
    lp5868_write_buffer(REG_DOT_CURRENT_BASE, fill_ff, LP5868_BYTES_PER_DRIVER);

    // re-enable chip
    wait_ms(10);
    lp5868_write_reg(REG_CHIP_EN, 0x00);
    wait_ms(10);
    lp5868_write_reg(REG_CHIP_EN, 0x01);
    wait_ms(10);

    // startup test
    lp5868_fill_pixel(0xff);
    lp5868_update();
    wait_ms(1000);

    // Set PWM to zero initially
    lp5868_fill_pixel(0);
    lp5868_update();
}

void lp5868_set_pixel(uint8_t x, uint8_t y, uint8_t brightness) {
    if (x >= LED_MATRIX_COLS || y >= LED_MATRIX_ROWS) return;
    lp5868_buffer[y][x] = brightness;
}

void lp5868_fill_pixel(uint8_t brightness) {
    memset(lp5868_buffer, brightness, sizeof(lp5868_buffer));
}

// Callback to turn off VSYNC pulse
static uint32_t lp5868_vsync_off(uint32_t trigger_time, void* cb_arg) {
    gpio_write_pin_low(LP5868_VSYNC_PIN);
    return 0; // Do not repeat
}

void lp5868_update(void) {
    // Write the entire buffer to the driver
    lp5868_write_buffer(REG_PWM_BRI_BASE, &lp5868_buffer[0][0], LP5868_BYTES_PER_DRIVER);

    // Generate VSYNC pulse to latch data. The original pulse width was 250us.
    gpio_write_pin_high(LP5868_VSYNC_PIN);
    // Defer turning off the VSYNC pulse by 1ms to avoid blocking the main loop
    defer_exec(1, lp5868_vsync_off, NULL);
}
