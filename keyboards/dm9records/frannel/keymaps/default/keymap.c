// Copyright 2024 Takuya Urakawa
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "frannel.h"

bool     enable_type_led = true;
uint16_t type_led_time   = 0;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortholinear(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,    KC_K,    KC_L,
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_J,    KC_K,    KC_L
    )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (enable_type_led && record->event.pressed) {
        type_led_time = timer_read();
        frannel_led_toggle_temp(1);
    }

    switch (keycode) {
        default:
            break;
    }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                enable_type_led = true;
                haptic_enable();
            } else {
                enable_type_led = false;
                frannel_led_restore();
                haptic_disable();
            }
            break;
        default:
            break;
    }
    return true;
}

void housekeeping_task_user(void) {
    if (enable_type_led && TIMER_DIFF_16(timer_read(), type_led_time) > TYPE_LED_DWELL) {
        frannel_led_restore();
    }
}
