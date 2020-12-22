/* Copyright 2020 hsgw
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
#include "keycode.h"
#include "keymap_jp.h"


#define NUM_SPC LT(NUM,KC_SPC)
#define S_SPC   LSFT_T(KC_SPC)
#define CTL_ZH  LCTL_T(JP_ZHTG)
#define FUNC_BS LT(FUNC,KC_BSPC)
#define TAB_CTL LCTL_T(KC_TAB)
#define G2_GUI LT(GAME2,KC_LGUI)
#define WIN_PS LSFT(LGUI(KC_S))
#define VS_FMT LSFT(LALT(KC_F))
#define S_ZKHK LSFT_T(JP_ZHTG)

enum layers {
    BASE, NUM, FUNC, CONF
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     JP_AT, \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,   JP_SCLN,  JP_COLN,\
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,    JP_COMM, JP_DOT, JP_SLSH,  JP_BSLS,\
                          KC_LALT, KC_LGUI, S_ZKHK, NUM_SPC, KC_TAB,    KC_ENT, KC_BSPC, MO(FUNC),JP_LBRC, JP_RBRC\
    ),
    [NUM] = LAYOUT(
        KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,     KC_7,    KC_8,      KC_9,      KC_0,      JP_YEN, \
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                    S(KC_6),  S(KC_7), S(KC_8),   S(KC_9),   JP_MINS,   S(JP_MINS), \
        _______, C(KC_Z), VS_FMT,  C(KC_C), C(KC_V), WIN_PS,                     KC_INS,   _______, S(JP_COMM),S(JP_DOT), S(JP_SLSH),JP_CIRC, \
                          _______, _______, _______, _______, _______,   _______, _______, _______, S(JP_LBRC),S(JP_RBRC) \
    ),
    [FUNC] = LAYOUT(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
        _______, _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
        _______, _______, _______, _______, _______, _______,                    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______ \
    ),
    [CONF] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, NUM, FUNC, CONF);
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case QMKBEST:
//             if (record->event.pressed) {
//                 // when keycode QMKBEST is pressed
//                 SEND_STRING("QMK is the best thing ever!");
//             } else {
//                 // when keycode QMKBEST is released
//             }
//             break;
//         case QMKURL:
//             if (record->event.pressed) {
//                 // when keycode QMKURL is pressed
//                 SEND_STRING("https://qmk.fm/\n");
//             } else {
//                 // when keycode QMKURL is released
//             }
//             break;
//     }
//     return true;
// }
