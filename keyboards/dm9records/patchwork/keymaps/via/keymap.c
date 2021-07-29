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

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4,
        KC_5, KC_6, KC_7, KC_8,
        MO(_FN), KC_0, KC_A, KC_B, KC_C,
        KC_UP,KC_DOWN
    ),
    [_FN] = LAYOUT(
        KC_X, KC_2, KC_3, KC_4,
        KC_5, KC_6, KC_7, KC_8,
        MO(_FN), KC_0, KC_A, KC_B, KC_C,
        KC_F,KC_R
    ),
    [2] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [3] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [4] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [5] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [6] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [7] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [8] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [9] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [10] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [11] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [12] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [13] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [14] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    ),
    [15] = LAYOUT(
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
        KC_NO,KC_NO
    )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) { return true; }
