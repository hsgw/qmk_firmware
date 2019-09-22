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

#define NUM_ENT LT(NUM_BASE, KC_ENTER)
#define OPT_SPC LT(OPT, KC_SPACE)
#define FUNC_ZKHK LT(FUNC,KC_ZKHK)
#define NUM_BSPC LT(NUM_BASE, KC_BSPC)

enum layers {
  BASE = 0,
  OPT,
  NUM_BASE,
  NUM_OPT,
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
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,     TD(TD_LBRC),\
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,      KC_G,     TD(TD_ASYM),\
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     NUM_BSPC,\
    KC_LCTL,  KC_LALT,  KC_LGUI,  MO(FUNC), FUNC_ZKHK, NUM_ENT,  OPT_SPC\
  ),
  [OPT] = LAYOUT( \
    KC_DEL,   KC_P,     KC_O,     KC_I,     KC_U,      KC_Y,      TD(TD_RBRC),\
    JP_COLN,  JP_SCLN,  KC_L,     KC_K,     KC_J,      KC_H,      TD(TD_BSYM),\
    _______,  JP_SLSH,  JP_DOT,   JP_COMM,  KC_M,      KC_N,      _______,\
    _______,  _______,  _______,  _______,  _______,   _______,   _______\
  ),
  [NUM_BASE] = LAYOUT( \
    KC_DEL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,\
    KC_TAB,   RS(KC_1), RS(KC_2), RS(KC_3), RS(KC_4), RS(KC_5), RS(KC_6),\
    _______,  JP_BSLS,  JP_SLSH,  KC_RABK,  KC_LABK,  JP_SLSH, _______,\
    _______,  _______,  _______,  _______,  _______,  _______,  _______\
  ),
  [NUM_OPT] = LAYOUT( \
    JP_CIRC,  JP_MINS,      KC_0,     KC_9,     KC_8,     KC_7,     XXXXXXX,\
    KC_JYEN,  RS(JP_MINS),  RS(KC_0), RS(KC_9), RS(KC_8), RS(KC_7), RS(KC_6),\
    _______,  JP_ASTR,      JP_RBRC,  KC_JYEN,  XXXXXXX,  XXXXXXX,  _______,\
    _______,  _______,      _______,  _______,  _______,  _______,  _______\
  ),
  [FUNC] = LAYOUT( \
    _______,  KC_PGUP,  KC_UP,    KC_PGDN,  _______,   _______,  RESET,\
    _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,   _______,  _______,\
    _______,  KC_INS,   KC_HOME,  KC_PSCR,  _______,   _______,  _______,\
    _______,  _______,  _______,  _______,  _______,   _______,  _______\
  ),
  [SYM] = LAYOUT(\
    KC_DEL,   RS(KC_1), RS(KC_2), RS(KC_3), RS(KC_4), RS(KC_5), RS(KC_6),\
    JP_SCLN,  RS(KC_7), RS(KC_8), RS(KC_9), JP_AT,    JP_CIRC, _______,\
    _______,  JP_COLN,  JP_BSLS,  JP_SLSH,  JP_COMM,  JP_DOT,  _______,\
    _______,  _______,  _______,  _______,  _______,  _______,  _______\
  )
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, OPT, NUM_BASE, NUM_OPT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    default:
      break;
  }
  return true;
}

