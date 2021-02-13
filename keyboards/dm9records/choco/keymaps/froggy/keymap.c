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
#include "keymap_jp.h"

#define RS(key) RSFT(key)

#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)

#define SYM_ENT LT(SYM, KC_ENTER)
#define OPT_SPC LT(OPT, KC_SPACE)
#define NUM_ZKHK LT(NUM,KC_ZKHK)

enum layers {
  BASE = 0,
  OPT,
  NUM,
  SYM,
  FUNC
};

// Defines the tapdance key code
enum custom_tapdances{
    TD_LBRC,
    TD_RBRC,
    TD_ASYM,
    TD_BSYM
};

uint16_t td_lbrc_keycodes[4] = {S(KC_8), JP_LBRC, S(JP_LBRC), S(JP_COMM)};

void td_lbrc_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count <= 4) {
        register_code16(td_lbrc_keycodes[state->count-1]);
    }
}

void td_lbrc_reset(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count <= 4) {
        unregister_code16(td_lbrc_keycodes[state->count-1]);
    }
}

uint16_t td_rbrc_keycodes[4] = {S(KC_9), JP_RBRC, S(JP_RBRC), S(JP_DOT)};

void td_rbrc_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count <= 4) {
        register_code16(td_rbrc_keycodes[state->count-1]);
    }
}

void td_rbrc_reset(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count <= 4) {
        unregister_code16(td_rbrc_keycodes[state->count-1]);
    }
}

uint16_t td_asym_keycodes[4] = {KC_COMMA, KC_DOT, S(KC_7), S(KC_2)};

void td_asym_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count <= 4) {
        register_code16(td_asym_keycodes[state->count-1]);
    }
}

void td_asym_reset(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count <= 4) {
        unregister_code16(td_asym_keycodes[state->count-1]);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
    [TD_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_lbrc_finished, td_lbrc_reset),
    [TD_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_rbrc_finished, td_rbrc_reset),
    [TD_ASYM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_asym_finished, td_asym_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT( \
    KC_ESC,   KC_P,     KC_K,     KC_R,     KC_A,      KC_F,     TD(TD_LBRC),\
    KC_TAB,   KC_D,     KC_T,     KC_H,     KC_E,      KC_O,     KC_BSPC,\
    KC_LSFT,  KC_Y,     KC_S,     KC_N,     KC_I,      KC_U,     TD(TD_ASYM),\
    KC_LCTL,  KC_LALT,  KC_LGUI,  MO(FUNC), NUM_ZKHK,  OPT_SPC,  SYM_ENT\
  ),
  [OPT] = LAYOUT( \
    KC_DEL,   KC_J,     KC_M,     KC_B,     KC_QUOT,   _______,  TD(TD_RBRC),\
    KC_BSPC,  KC_V,     KC_C,     KC_L,     KC_Z,     KC_Q,      _______,\
    _______,  KC_X,     KC_G,     KC_W,     KC_MINUS,  _______,  TD(TD_BSYM),\
    _______,  _______,  _______,  _______,  _______,   _______,  _______\
  ),
  [NUM] = LAYOUT( \
    _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,\
    _______,  KC_7,     KC_8,     KC_9,     KC_0,     JP_MINS, _______,\
    _______,  JP_MINS,  JP_PLUS,  JP_ASTR,  JP_SLSH,  KC_JYEN, TD(TD_ASYM),\
    _______,  _______,  _______,  _______,  _______,  _______,  _______\
  ),
  [FUNC] = LAYOUT( \
    _______,  KC_PGUP,  KC_UP,    KC_PGDN,  _______,   _______,  RESET,\
    _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,   _______,  _______,\
    _______,  KC_INS,   KC_HOME,  KC_PSCR,  _______,   _______,  _______,\
    _______,  _______,  _______,  _______,  _______,   _______,  _______\
  ),
  [SYM] = LAYOUT(\
    _______,  RS(KC_1), RS(KC_2), RS(KC_3), RS(KC_4), RS(KC_5), RS(KC_6),\
    JP_SCLN,  RS(KC_7), RS(KC_8), RS(KC_9), JP_AT,    JP_CIRC,  _______,\
    _______,  JP_COLN,  JP_BSLS,  JP_SLSH,  JP_COMM,  JP_DOT,  _______,\
    _______,  _______,  _______,  _______,  _______,  _______,  _______\
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    default:
      break;
  }
  return true;
}

