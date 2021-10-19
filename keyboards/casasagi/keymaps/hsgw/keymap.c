
/* Copyright 2021 Takuya Urakawa, Dm9Recoreds.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_jp.h"

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
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    S(KC_8),        S(KC_9),  KC_Y,    KC_U,    KC_I,      KC_O,      KC_P,      JP_AT, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    JP_LBRC,        JP_RBRC,  KC_H,    KC_J,    KC_K,      KC_L,      JP_SCLN,   JP_COLN,\
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,           KC_INS,   KC_N,    KC_M,    JP_COMM,   JP_DOT,    JP_SLSH,   JP_CIRC,\
        KC_LALT, KC_LALT, KC_LALT, KC_LGUI, JP_ZHTG, NUM_SPC, KC_TAB,         FUNC_ENT, KC_BSPC, MO(FUNC),JP_LBRC,   JP_RBRC,   JP_BSLS,   JP_YEN\
    ),
    [NUM] = LAYOUT(
        KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,        _______,  KC_6,    KC_7,    KC_8,      KC_9,      KC_0,      JP_YEN, \
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(JP_LBRC),    S(JP_RBRC),S(KC_6), S(KC_7), S(KC_8),   S(KC_9),   JP_MINS,   S(JP_MINS),\
        _______, C(KC_Z), VS_FMT,  C(KC_C), C(KC_V), WIN_PS,  S(JP_MINS),     VS_FMT,   JP_LBRC, JP_RBRC, S(JP_COMM),S(JP_DOT), S(JP_SLSH),S(JP_CIRC), \
        _______, _______, _______, _______, _______, _______, _______,        _______,  _______, _______, S(JP_LBRC),S(JP_RBRC),S(JP_BSLS),S(JP_YEN) \
    ),
    [FUNC] = LAYOUT(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
        _______, _______, _______, _______, _______, _______, _______,        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_F12,  \
        _______, _______, _______, C(KC_C), C(KC_V), _______, _______,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______  \
    ),
    [CONF] = LAYOUT(
        RESET,   RGB_TOG, RGB_HUI, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,        EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RESET, \
        _______, RGB_MOD, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        _______, RGB_SPI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,        _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, TG(GAME) \
    ),
    [GAME] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_1,           S(KC_9),  KC_Y,    KC_U,    KC_I,      KC_O,      KC_P,      JP_AT, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_2,           JP_RBRC,  KC_H,    KC_J,    KC_K,      KC_L,      JP_SCLN,   JP_COLN,\
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_3,           KC_INS,   KC_N,    KC_M,    JP_COMM,   JP_DOT,    JP_SLSH,   JP_CIRC,\
        KC_LALT, KC_LALT, KC_LALT, KC_LGUI, MO(NUM), KC_SPC,  KC_TAB,         FUNC_ENT, KC_BSPC, MO(FUNC),JP_LBRC,   JP_RBRC,   JP_BSLS,   TG(GAME)\
    ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, NUM, FUNC, CONF); }
