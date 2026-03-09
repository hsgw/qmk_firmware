// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "platforms/gpio.h"

// Previous raw matrix state to detect changes
static matrix_row_t prev_raw_matrix[MATRIX_ROWS] = {0};

void matrix_init_custom(void) {
    // Initialize 74HC138 address pins as outputs
    gpio_set_pin_output_push_pull(HC138_ADDR_0);
    gpio_set_pin_output_push_pull(HC138_ADDR_1);
    gpio_set_pin_output_push_pull(HC138_ADDR_2);

    // Initialize 74HC165 pins
    gpio_set_pin_output_push_pull(HC165_LATCH);
    gpio_write_pin_high(HC165_LATCH); // Latch high initially

    gpio_set_pin_output_push_pull(HC165_CLOCK);
    gpio_write_pin_low(HC165_CLOCK); // Clock low initially

    // Initialize 74HC165 data input pins
    gpio_set_pin_input_high(HC165_DATA); // Input with pull-up
#ifdef JUROKUHACHI_256
    gpio_set_pin_input_high(HC165_DATA_2);
#endif

    // Initialize previous raw matrix state
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        prev_raw_matrix[r] = 0;
    }
}

// Custom matrix scan function
// It updates the current_matrix buffer passed by QMK
// and returns true if any key state changed from the previous scan.
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool         changed          = false;
    matrix_row_t current_row_data = 0;
#ifdef JUROKUHACHI_256
    matrix_row_t current_row_data_2 = 0;
#endif

    // Scan 74HC138 addresses (0 to 7)
    // Board 1 occupies rows 0-7, Board 2 occupies rows 8-15 (if 256 mode)
    for (uint8_t row_addr = 0; row_addr < 8; ++row_addr) {
        // Step 1: Row selection using 74HC138
        gpio_write_pin(HC138_ADDR_0, (row_addr >> 0) & 1);
        gpio_write_pin(HC138_ADDR_1, (row_addr >> 1) & 1);
        gpio_write_pin(HC138_ADDR_2, (row_addr >> 2) & 1);
        wait_us(1); // Small delay for the 74HC138 to settle

        // Step 2: Key state latch using 74HC165
        gpio_write_pin_low(HC165_LATCH);  // Pulse Low to load data
        wait_us(1);                       // Small delay for latch pulse
        gpio_write_pin_high(HC165_LATCH); // Latch high

        // Step 3: Data serial reading from 74HC165s
        current_row_data = 0;
#ifdef JUROKUHACHI_256
        current_row_data_2 = 0;
#endif
        for (int bit = 0; bit < 16; ++bit) { // Read 16 bits
            bool bit_val = gpio_read_pin(HC165_DATA);
            current_row_data |= ((!bit_val) << (16 - 1 - bit));

#ifdef JUROKUHACHI_256
            bool bit_val_2 = gpio_read_pin(HC165_DATA_2);
            current_row_data_2 |= ((!bit_val_2) << (16 - 1 - bit));
#endif

            // Clock Pulse
            gpio_write_pin_high(HC165_CLOCK);
            wait_us(1); // Small delay for clock pulse
            gpio_write_pin_low(HC165_CLOCK);
        }

        // Update Board 1 rows
        if (current_row_data != prev_raw_matrix[row_addr]) {
            changed                   = true;
            prev_raw_matrix[row_addr] = current_row_data;
        }
        current_matrix[row_addr] = current_row_data;

#ifdef JUROKUHACHI_256
        // Update Board 2 rows (offset by 8)
        if (current_row_data_2 != prev_raw_matrix[row_addr + 8]) {
            changed                       = true;
            prev_raw_matrix[row_addr + 8] = current_row_data_2;
        }
        current_matrix[row_addr + 8] = current_row_data_2;
#endif
    }

    return changed;
}
