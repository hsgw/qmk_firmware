// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

#define NUM_SPC LT(NUM, KC_SPC)
#define S_SPC LSFT_T(KC_SPC)
#define CTL_ZH LCTL_T(JP_ZHTG)
#define FUNC_BS LT(FUNC, KC_BSPC)
#define FUNC_ENT LT(FUNC, KC_ENT)
#define WIN_PS LSFT(LGUI(KC_S))
#define VS_FMT LSFT(LALT(KC_F))
#define SFT_ZK LSFT_T(JP_ZHTG)

enum layers { BASE, NUM, FUNC, CONF, GAME };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,      KC_O,      KC_P,      JP_AT, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,      KC_L,      JP_SCLN,   JP_COLN,\
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    JP_COMM,   JP_DOT,    JP_SLSH,   JP_CIRC,\
        KC_LALT, KC_LALT, KC_LGUI, KC_TAB,  JP_ZKHK, NUM_SPC,         FUNC_ENT,KC_BSPC, JP_LBRC,   JP_RBRC,   JP_BSLS,   JP_YEN\
    ),
    [NUM] = LAYOUT(
        KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,      KC_9,      KC_0,      JP_YEN, \
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),         S(KC_6), S(KC_7), S(KC_8),   S(KC_9),   JP_MINS,   S(JP_MINS),\
        _______, C(KC_Z), KC_INS,  C(KC_C), C(KC_V), WIN_PS,          JP_LBRC, JP_RBRC, S(JP_COMM),S(JP_DOT), S(JP_SLSH),S(JP_CIRC), \
        _______, _______, _______, _______, _______, _______,         _______, _______, S(JP_LBRC),S(JP_RBRC),S(JP_BSLS),S(JP_YEN) \
    ),
    [FUNC] = LAYOUT(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
        _______, _______, _______, _______, _______, _______,         KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_F12,  \
        _______, _______, _______, C(KC_C), C(KC_V), _______,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
        _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______  \
    ),
    [CONF] = LAYOUT(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,          EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, \
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, TG(GAME) \
    ),
    [GAME] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,      KC_O,      KC_P,      JP_AT, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,      KC_L,      JP_SCLN,   JP_COLN,\
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    JP_COMM,   JP_DOT,    JP_SLSH,   JP_CIRC,\
        KC_LALT, KC_LALT, KC_LALT, KC_LGUI, MO(NUM), KC_SPC,           FUNC_ENT,KC_BSPC, JP_LBRC,   JP_RBRC,   JP_BSLS,   TG(GAME)\
    ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, NUM, FUNC, CONF);
}
