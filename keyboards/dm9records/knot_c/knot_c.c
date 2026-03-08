#include "quantum.h"
#include "i2c_master.h"
#include "cy8cmbr3108.h"

#ifdef KNOT_C_DEBUG
#    include "print.h"
#endif

void keyboard_pre_init_kb(void) {
    gpio_set_pin_input(GP6);
    gpio_set_pin_input(GP7);
    i2c_init();

#ifndef KNOT_C_DEBUG
    // Normal boot initialization
    wait_ms(15);
    cy8cmbr3108_init();
#endif

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
#ifdef KNOT_C_DEBUG
    // Debug initialization with delay for USB console
    debug_enable = true;
    wait_ms(5000);
    uprintf("KNOT-C: Debug mode enabled.\n");
    cy8cmbr3108_init();
#endif

    keyboard_post_init_user();
}

extern matrix_row_t matrix[MATRIX_ROWS];

void matrix_scan_kb(void) {
    if (cy8cmbr3108_is_ready()) {
        uint16_t     btn_stat = cy8cmbr3108_read();
        matrix_row_t row      = matrix[0];

        // Map bits to matrix row (0x04 -> Bit 1, 0x20 -> Bit 2)
        if (btn_stat & 0x04)
            row |= (1 << 1);
        else
            row &= ~(1 << 1);

        if (btn_stat & 0x20)
            row |= (1 << 2);
        else
            row &= ~(1 << 2);

        matrix[0] = row;
    }

    matrix_scan_user();
}
