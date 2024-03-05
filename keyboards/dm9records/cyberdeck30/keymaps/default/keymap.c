// Copyright 2024 hsgw
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <keymap_japanese.h>

// clang-format off

// combo
const uint16_t PROGMEM combo_esc[]  = {LT(4, KC_Q), KC_W, COMBO_END};
const uint16_t PROGMEM combo_del[]  = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_ent[]  = {KC_L, RCTL_T(JP_SCLN), COMBO_END};
const uint16_t PROGMEM combo_spc[]  = {RALT_T(JP_DOT), RSFT_T(JP_SLSH), COMBO_END};
const uint16_t PROGMEM combo_tab[]  = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_zkhk[] = {LGUI_T(KC_C), KC_V, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_del, KC_DEL),
    COMBO(combo_bspc, KC_BSPC),
    COMBO(combo_ent, KC_ENT),
    COMBO(combo_spc, KC_SPC),
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_zkhk, JP_ZKHK)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, 1, 2, 3);
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x10(
        LT(4,KC_Q),   KC_W,         KC_E,         KC_R, KC_T,       KC_Y,       KC_U,    KC_I,    KC_O,           KC_P,
        LCTL_T(KC_A), KC_S,         KC_D,         KC_F, KC_G,       KC_H,       KC_J,    KC_K,    KC_L,           RCTL_T(JP_SCLN),
        LSFT_T(KC_Z), LALT_T(KC_X), LGUI_T(KC_C), KC_V, LT(1,KC_B), LT(2,KC_N), KC_M,    JP_COMM, RALT_T(JP_DOT), RSFT_T(JP_SLSH)
    ),
    [1] = LAYOUT_ortho_3x10(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0),
        _______, _______, _______, _______, _______, _______, JP_MINS, JP_LBRC, JP_RBRC, KC_BSLS
    ),
    [2] = LAYOUT_ortho_3x10(
        _______, _______, _______, _______, KC_PSCR, _______, _______, _______, _______,  _______,
        KC_LCTL, _______, _______, _______, KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
        KC_LSFT, KC_LALT, KC_LGUI, _______, _______, _______, _______, JP_AT,   JP_CIRC,  JP_YEN
    ),
    [3] = LAYOUT_ortho_3x10(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [4] = LAYOUT_ortho_3x10(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, KC_MS_U, KC_WH_U, XXXXXXX,
        KC_LCTL, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_RCTL,
        KC_LSFT, KC_LALT, KC_LGUI, C(KC_C), C(KC_V), XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, KC_RSFT
    ),

};

// clang-format on
