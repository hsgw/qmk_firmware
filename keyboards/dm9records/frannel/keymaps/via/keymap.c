// Copyright 2024 Takuya Urakawa
// SPDX-License-Identifier: GPL-2.0-or-later

// based on plaid default keymap

#include QMK_KEYBOARD_H
#include "frannel.h"

enum layers {
    BASE = 0,
    UPPER,
    LOWER,
    ADJUST,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ortho(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        KC_LALT, KC_RALT, KC_LALT, KC_LGUI, TL_LOWR, KC_SPC,  KC_SPC,  TL_UPPR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [UPPER] = LAYOUT_ortho(
        _______, _______, _______, _______, _______,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [LOWER] = LAYOUT_ortho(
        _______, KC_NUM,  KC_CAPS, _______, _______,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    )
};
// clang-format on

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        if (active) {
            frannel_solenoid_enable(true);
            frannel_haptic_led_enable(true);
        } else {
            frannel_solenoid_enable(false);
            frannel_haptic_led_enable(false);
        }
        return false;
    }
    return true;
}
