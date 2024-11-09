#include "matrix.h"
#include "wait.h"

#define PIN_165_DATA B0
#define PIN_165_CLK B1
#define PIN_165_LOAD B2

#define NUM_165_DATA 8

#define WAIT_165() wait_us(5)

void matrix_init_custom(void) {
    gpio_set_pin_input(PIN_165_DATA);
    gpio_set_pin_output(PIN_165_CLK);
    gpio_set_pin_output(PIN_165_LOAD);
    gpio_write_pin_high(PIN_165_LOAD);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // LOAD pulse
    gpio_write_pin_low(PIN_165_LOAD);
    WAIT_165();
    gpio_write_pin_high(PIN_165_LOAD);
    WAIT_165();

    uint8_t current_state = 0;

    for (uint8_t i = 0; i < NUM_165_DATA; i++) {
        // read switch
        current_state |= gpio_read_pin(PIN_165_DATA) ? 0 : 1 << i;

        // clock pulse
        gpio_write_pin_high(PIN_165_CLK);
        WAIT_165();
        gpio_write_pin_low(PIN_165_CLK);
    }

    if (current_state != current_matrix[0]) {
        matrix_has_changed = true;
        current_matrix[0]  = current_state;
    }

    return matrix_has_changed;
}
