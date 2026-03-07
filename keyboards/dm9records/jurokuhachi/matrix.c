// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "config.h"         // Include our config for pin definitions
#include "platforms/gpio.h" // Include QMK's GPIO abstraction

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

    // Initialize 74HC165 data input pin (single data line)
    gpio_set_pin_input_high(HC165_DATA); // Input with pull-up

    // Initialize previous raw matrix state
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        prev_raw_matrix[r] = 0;
    }
}

// Custom matrix scan function
// It updates the current_matrix buffer passed by QMK
// and returns true if any key state changed from the previous scan.
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool         changed          = false; // Flag to indicate if any key state has changed
    matrix_row_t current_row_data = 0;     // To store the 16-bit data for the current row

    // Scan 74HC138 addresses (0 to 7) for 8 rows
    for (uint8_t row_addr = 0; row_addr < MATRIX_ROWS; ++row_addr) {
        // Step 1: Row selection using 74HC138
        // Set the 74HC138 address pins
        gpio_write_pin(HC138_ADDR_0, (row_addr >> 0) & 1);
        gpio_write_pin(HC138_ADDR_1, (row_addr >> 1) & 1);
        gpio_write_pin(HC138_ADDR_2, (row_addr >> 2) & 1);
        wait_us(1); // Small delay for the 74HC138 to settle

        // Step 2: Key state latch using 74HC165
        gpio_write_pin_low(HC165_LATCH);  // Pulse Low to load data
        wait_us(1);                       // Small delay for latch pulse
        gpio_write_pin_high(HC165_LATCH); // Latch high

        // Step 3: Data serial reading from 74HC165s (16 bits from a single data line)
        current_row_data = 0;                         // Reset for each row
        for (int bit = 0; bit < MATRIX_COLS; ++bit) { // Read MATRIX_COLS (16) bits
            bool bit_val = gpio_read_pin(HC165_DATA);

            // Active Low (0 when pressed) -> Invert to 1
            current_row_data |= ((!bit_val) << (MATRIX_COLS - 1 - bit));

            // Clock Pulse
            gpio_write_pin_high(HC165_CLOCK);
            wait_us(1); // Small delay for clock pulse
            gpio_write_pin_low(HC165_CLOCK);
        }

        // Update the current_matrix buffer passed by QMK
        // Check for changes
        if (current_row_data != prev_raw_matrix[row_addr]) {
            changed                   = true;
            prev_raw_matrix[row_addr] = current_row_data; // Update previous state
        }
        current_matrix[row_addr] = current_row_data; // Update the passed matrix
    }

    return changed; // Return true if any key state changed
}
