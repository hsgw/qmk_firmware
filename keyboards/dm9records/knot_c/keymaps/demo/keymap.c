// Copyright 2026 Takuya Urakawa @hsgw (5z6p.ccom)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Adjustment factor for scroll sensitivity
// Increase this value to slow down the scroll speed.
#define SCROLL_DIVISOR 4

// Define layers
enum layers { _BASE, _SCROLL = 4 };

// Define keycodes
enum custom_keycodes { TOUCH_L = SAFE_RANGE, TOUCH_R };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        TOUCH_L, TOUCH_R, MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4 // 2 Touch, 4 Physical
    ),
    [_SCROLL] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
// clang-format on

// Accumulators for smooth scrolling (avoid losing slow movements)
static int16_t scroll_x_remainder = 0;
static int16_t scroll_y_remainder = 0;

// Handle trackball to High Resolution Scroll conversion
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (IS_LAYER_ON(_SCROLL)) {
        // Accumulate trackball movement to capture slow rotations
        scroll_x_remainder += mouse_report.x;
        scroll_y_remainder -= mouse_report.y; // Invert Y for natural scrolling

        // Calculate scroll amount based on accumulated values and divisor
        mouse_report.h = scroll_x_remainder / SCROLL_DIVISOR;
        mouse_report.v = scroll_y_remainder / SCROLL_DIVISOR;

        // Keep the remainder for the next task cycle
        scroll_x_remainder %= SCROLL_DIVISOR;
        scroll_y_remainder %= SCROLL_DIVISOR;

        // Prevent mouse cursor from moving
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        // Reset remainders when not in scroll mode to avoid "ghost" scrolling
        scroll_x_remainder = 0;
        scroll_y_remainder = 0;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TOUCH_L:
            if (record->event.pressed) {
                layer_on(_SCROLL);
                register_code(KC_F15);
            } else {
                unregister_code(KC_F15);
                layer_off(_SCROLL);
            }
            return false;

        case TOUCH_R:
            if (record->event.pressed) {
                layer_on(_SCROLL);
                register_code(KC_F16);
            } else {
                unregister_code(KC_F16);
                layer_off(_SCROLL);
            }
            return false;
    }
    return true;
}
