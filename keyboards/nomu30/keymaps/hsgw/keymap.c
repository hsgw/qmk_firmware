/* Copyright 2019 Naoto Takai, Takura Urakawa(dm9records.com, 5z6p.com)
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

#define _BASE 0
#define _NUMS 1
#define _SYMS 2
#define _FUNC 3

enum {
  TD_DOT = 0,
  TD_BRC,
  TD_COLN
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_DOT] = ACTION_TAP_DANCE_DOUBLE(JP_COMM, JP_DOT),
  [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(JP_LBRC, JP_RBRC),
  [TD_COLN] = ACTION_TAP_DANCE_DOUBLE(JP_SCLN, JP_COLN)
};



#define CT_TAB MT(MOD_LCTL, KC_TAB)
#define AL_Z   LALT_T(KC_Z)
#define GUI_X  LGUI_T(KC_X)
#define NUM_V  LT(_NUMS, KC_V)
#define FUNC_N LT(_FUNC, KC_N)
#define SYMS_B LT(_SYMS, KC_B)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CT_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_LSFT, AL_Z,    GUI_X,   KC_C,    NUM_V,   SYMS_B,  FUNC_N,  KC_M,    KC_SPC
    ),
    [_NUMS] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    JP_YEN,
        _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), KC_MINUS,
        _______, _______, _______, _______, _______, JP_CIRC, JP_COMM, JP_DOT,  TD_COLN
    ),
    [_SYMS] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, _______, JP_UNDS, JP_CIRC, JP_AT,   JP_LBRC, KC_DEL,
        _______, JP_EXLM, JP_QUES, JP_TILD, JP_PIPE, JP_EQL,  JP_SLSH, JP_SCLN, JP_COLN, JP_RBRC, KC_ENT,
        _______, _______, _______, _______, JP_ZHTG, _______, _______, JP_BSLS, KC_SPC
    ),
    [_FUNC] = LAYOUT(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_F9,   KC_F10,
        C(KC_TAB), _______, _______, _______, _______, KC_INS,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______,
        _______,   KC_LALT, KC_LGUI, _______, _______, _______, _______, _______, _______
    )
};
