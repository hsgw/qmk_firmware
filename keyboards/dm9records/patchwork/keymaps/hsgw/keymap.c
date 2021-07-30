/* Copyright 2021 Takuya Urakawa
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

#define CK(keycode) LT(_CONF, keycode)
#define FN(layer, keycode) LT(_##layer##_FN, keycode)

// Defines names for use in layer keycodes and the keymap
enum layer_names { _0, _0_FN, _1, _1_FN, _2, _2_FN, _3, _3_FN, _4, _4_FN, _5, _5_FN, _6, _6_FN, _CONF, _CONF_FN };

// Start from via user keycode
enum custom_keycode { RGB_VNI = USER00, RGB_VND, RGB_SAVE };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_0] = LAYOUT(
        CK(KC_BSPC),KC_P7, KC_P8, KC_P9,
        KC_DOT,     KC_P4, KC_P5, KC_P6,
        KC_P0,      KC_P1, KC_P2, FN(0, KC_P3), KC_PENT,
        KC_LEFT,    KC_RIGHT
    ),
    [_0_FN] = LAYOUT(
        KC_DEL,  KC_PPLS, KC_PMNS, JP_EQL,
        KC_COMM, KC_PAST, KC_PSLS, KC_COMM,
        KC_SPC,  JP_LPRN, JP_RPRN, _______, KC_NLCK,
        _______, _______
    ),
    [_1] = LAYOUT(
        CK(KC_ESC), KC_X,     KC_E,      KC_R,
        KC_LSFT,    KC_V,     RCS(KC_M), KC_D,
        RCTL(KC_Z), KC_N,     RCS(KC_M), FN(1, KC_SLSH), KC_A,
        RSFT(KC_W), KC_W
    ),
    [_1_FN] = LAYOUT(
        KC_DEL,     RCS(KC_Z), RCTL(KC_R), KC_F,
        _______,    RCS(KC_V), RCS(KC_H),  RCS(KC_T),
        RCTL(KC_Y), RSFT(KC_N),RCTL(KC_S), _______,  _______,
        JP_YEN, RSFT(KC_7)
    ),
    [_2] = LAYOUT(
        CK(KC_ESC),KC_W,      KC_A,  KC_R,
        KC_TAB,    KC_L,      KC_G,  KC_M,
        RCTL(KC_Z),RCTL(KC_V),KC_INS,FN(2, KC_E),KC_C,
        KC_UP,KC_DOWN
    ),
    [_2_FN] = LAYOUT(
        KC_DEL,    KC_B,      KC_Q,   KC_Y,
        KC_M,      KC_H,      KC_J,   RCTL(KC_S),
        RCTL(KC_Y),RCTL(KC_C),_______,_______,_______,
        _______, _______
    ),
    [_3] = LAYOUT(
        MO(_CONF),KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_3_FN] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_4] = LAYOUT(
        MO(_CONF),KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_4_FN] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_5] = LAYOUT(
        MO(_CONF),KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_5_FN] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_6] = LAYOUT(
        MO(_CONF),KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_6_FN] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [_CONF] = LAYOUT(
        MO(_CONF), TO(_0), TO(_1),  TO(_2),
        TO(_3),     TO(_4), TO(_5), TO(_6),
        RESET,      KC_NO,  KC_NO,  RGB_SAVE, RGB_TOG,
        RGB_VND,RGB_VNI
    ),
    [_CONF_FN] = LAYOUT(
        MO(_CONF),KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_VNI:
            if (record->event.pressed) {
                rgb_matrix_increase_val_noeeprom();
                return false;
            }
            break;
        case RGB_VND:
            if (record->event.pressed) {
                rgb_matrix_decrease_val_noeeprom();
                return false;
            }
            break;
        case RGB_SAVE:
            if (record->event.pressed) {
                eeconfig_update_rgb_matrix();
                return false;
            }
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);
    uint8_t layer_number  = current_layer / 2;
    uint8_t val           = rgb_matrix_get_val();
    if (current_layer == 0)
        rgb_matrix_sethsv_noeeprom(148, 0, val);
    else if (current_layer == 1)
        rgb_matrix_sethsv_noeeprom(148, 64, val);
    else
        rgb_matrix_sethsv_noeeprom(layer_number * 32, current_layer % 2 == 0 ? 255 : 192, val);
    return state;
}
