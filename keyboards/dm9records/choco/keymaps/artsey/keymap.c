/* Copyright 2019 Takuya Urakawa, Dm9Recoreds.com
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
#include "artsey.h"
#include "keymap_combo.h"
#include "artsey.c"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_A_BASE] = LAYOUT(
    KC_NO,A_BASE_S,A_BASE_T,A_BASE_R,A_BASE_A,KC_NO,KC_NO,
    KC_NO,A_BASE_O,A_BASE_I,A_BASE_Y,A_BASE_E,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),

[_A_NUM] = LAYOUT(
    KC_NO,A_NUM_S,A_NUM_T,A_NUM_R,A_NUM_A,KC_NO,KC_NO,
    KC_NO,A_NUM_O,A_NUM_I,A_NUM_Y,A_NUM_E,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),

[_A_NAV] = LAYOUT(
    KC_NO,A_NAV_S,A_NAV_T,A_NAV_R,A_NAV_A,KC_NO,KC_NO,
    KC_NO,A_NAV_O,A_NAV_I,A_NAV_Y,A_NAV_E,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),

[_A_SYM] = LAYOUT(
    KC_NO,A_SYM_S,A_SYM_T,A_SYM_R,A_SYM_A,KC_NO,KC_NO,
    KC_NO,A_SYM_O,A_SYM_I,A_SYM_Y,A_SYM_E,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),

[_A_BRAC] = LAYOUT(
    KC_NO,A_BRAC_S,A_BRAC_T,A_BRAC_R,A_BRAC_A,KC_NO,KC_NO,
    KC_NO,A_BRAC_O,A_BRAC_I,A_BRAC_Y,A_BRAC_E,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),

[_A_MOU] = LAYOUT(
    KC_NO,A_MOU_S,A_MOU_T,A_MOU_R,A_MOU_A,KC_NO,KC_NO,
    KC_NO,A_MOU_O,A_MOU_I,A_MOU_Y,A_MOU_E,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),

[_A_CUSTOM] = LAYOUT(
    KC_NO,A_CUSTOM_S,A_CUSTOM_T,A_CUSTOM_R,A_CUSTOM_A,KC_NO,KC_NO,
    KC_NO,A_CUSTOM_O,A_CUSTOM_I,A_CUSTOM_Y,A_CUSTOM_E,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO),
};
// clang-format on
