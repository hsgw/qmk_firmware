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

// #define SYM_ENT LT(SYM, KC_ENTER)
// #define OPT_SPC LT(OPT, KC_SPACE)
// #define NUM_ZKHK LT(NUM,KC_ZKHK)

enum layers {
  BASE = 0,
  OPT,
  NUM,
  SYM,
  TENKEY,
  TENKEY_ALT,
  FUNC
};

enum custom_keycodes {
    SYM_ENT = SAFE_RANGE,
    OPT_SPC,
    NUM_ZKHK
};

#define DELAY_TIME  75
static uint16_t key_timer;
static uint16_t tap_timer;
static uint16_t delay_registered_code;
static uint8_t delay_mat_row;
static uint8_t delay_mat_col;
static bool delay_key_stat;
static bool delay_key_pressed;
static bool tapping_key;

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( keymaps[BASE][i][j] == keycode){
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}

void unregister_delay_code(void){
  if(delay_registered_code){
    unregister_code(delay_registered_code);
    if (delay_registered_code & QK_LSFT){
      unregister_code(KC_LSFT);
    }
    if (delay_registered_code & QK_LCTL){
      unregister_code(KC_LCTL);
    }
    if (delay_registered_code & QK_LALT){
      unregister_code(KC_LALT);
    }
    if (delay_registered_code & QK_LGUI){
      unregister_code(KC_LGUI);
    }
    delay_registered_code=0;
  }
}

void register_delay_code(uint8_t layer){
  if(delay_key_stat){
    unregister_delay_code();

    uint16_t code = pgm_read_word(&(keymaps[layer][delay_mat_row][delay_mat_col]));
    if (code & QK_RSFT){
      register_code(KC_RSFT);
    }
    if (code & QK_RCTL){
      register_code(KC_RCTL);
    }
    if (code & QK_RALT){
      register_code(KC_RALT);
    }
    if (code & QK_RGUI){
      register_code(KC_RGUI);
    }
    register_code(code);
    delay_registered_code = code;
    delay_key_stat = false;
    tapping_key = true;
  }
}

void process_tap(bool isPressed, uint8_t layer, uint16_t tap) {
  if (isPressed) {
    tapping_key = false;
    register_delay_code(layer);
    layer_on(layer);
    tap_timer = timer_read();
  } else {
    layer_off(layer);
    if (tapping_key == false && timer_elapsed(tap_timer) < TAPPING_TERM) {
      tap_code(tap);
    }
    tap_timer = 0;
  }
}

// Defines the tapdance key code
enum custom_tapdances{
    TD_LBRC,
    TD_RBRC,
    TD_ASYM,
    TD_BSYM,
    TD_DOT,
    TD_COLN
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
    [TD_DOT] =  ACTION_TAP_DANCE_DOUBLE(JP_COMM, JP_DOT),
    [TD_COLN] = ACTION_TAP_DANCE_DOUBLE(JP_SCLN, JP_COLN)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT( \
    KC_ESC,   KC_MINUS, KC_S,     KC_K,     KC_T,      KC_Y,     TD(TD_LBRC),\
    KC_TAB,   KC_A,     KC_O,     KC_E,     KC_I,      KC_U,     KC_BSPC,\
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     TD(TD_ASYM),\
    KC_LCTL,  KC_LALT,  KC_LGUI,  MO(FUNC), NUM_ZKHK,  OPT_SPC,  SYM_ENT\
  ),
  [OPT] = LAYOUT( \
    KC_DEL,   JP_DOT,     KC_W,     KC_F,     KC_R,    JP_UNDS,  TD(TD_RBRC),\
    _______,  JP_COMM,    KC_M,     KC_D,     KC_N,    KC_H,     _______,\
    _______,  KC_P,       KC_Q,     KC_L,     KC_G,    KC_J,     _______,\
    _______,  _______,    _______,  _______,  _______, _______,  _______\
  ),
  [NUM] = LAYOUT( \
    _______,  KC_7,     KC_8,     KC_9,   XXXXXXX,     XXXXXXX, XXXXXXX,\
    _______,  KC_4,     KC_5,     KC_6,   XXXXXXX,     XXXXXXX, _______,\
    _______,  KC_1,     KC_2,     KC_3,   JP_SLSH,  KC_JYEN,    _______,\
    _______,  KC_0,     KC_COMM,  KC_DOT, _______,  _______,    _______\
  ),
  [FUNC] = LAYOUT( \
    _______,  KC_PGUP,  KC_UP,    KC_PGDN,  _______,   TG(TENKEY), RESET,\
    _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,   _______,  _______,\
    _______,  KC_INS,   KC_HOME,  KC_PSCR,  _______,   _______,  _______,\
    _______,  _______,  _______,  _______,  _______,   _______,  _______\
  ),
  [SYM] = LAYOUT(\
    _______,  RS(KC_1), RS(KC_2), RS(KC_3), RS(KC_4), RS(KC_5), RS(KC_6),\
    JP_SCLN,  RS(KC_7), RS(KC_8), RS(KC_9), JP_AT,    JP_CIRC,  _______,\
    _______,  JP_COLN,  JP_BSLS,  JP_SLSH,  JP_COMM,  JP_DOT,  _______,\
    _______,  _______,  _______,  _______,  _______,  _______,  _______\
  ),
  [TENKEY] = LAYOUT(\
    KC_ESC,   KC_7,     KC_8,     KC_9,     XXXXXXX,  TG(TENKEY),XXXXXXX,\
    KC_TAB,   KC_4,     KC_5,     KC_6,     KC_COMM,  XXXXXXX,  XXXXXXX,\
    S(C(KC_Z)),KC_1,    KC_2,     KC_3,     KC_DOT,   XXXXXXX,  XXXXXXX,\
    C(KC_Z),  KC_0,     TD(TD_LBRC),  TD(TD_RBRC),   LT(TENKEY_ALT,KC_BSPC),  _______,  _______\
  ),
  [TENKEY_ALT] = LAYOUT(\
    KC_DEL,  _______,  _______,  _______,  _______,  _______,  _______,\
    _______,  _______,  _______,  _______,  _______,  _______,  _______,\
    C(KC_C),  _______,  _______,  _______,  _______,  _______,  _______,\
    C(KC_V),  _______,  _______,  _______,  _______,  _______,  _______\
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(tap_timer && keycode != SYM_ENT && keycode != OPT_SPC && keycode != NUM_ZKHK) {
      tapping_key = true;
  }

  if(keycode==delay_registered_code){
      if (!record->event.pressed){
        unregister_delay_code();
      }
  }

  switch (keycode) {
    case KC_ESC:
    case KC_TAB:
    case KC_MINUS:
    case KC_K:
    case KC_T:
    case KC_S:
    case KC_Y:
    case KC_A:
    case KC_O:
    case KC_E:
    case KC_I:
    case KC_U:
    case KC_BSPC:
    case KC_Z:
    case KC_X:
    case KC_C:
    case KC_V:
    case KC_B:
      if (record->event.pressed) {
        register_delay_code(BASE);
        if (find_mairix(keycode, &delay_mat_row, &delay_mat_col)) {
          key_timer         = timer_read();
          delay_key_stat    = true;
          delay_key_pressed = true;
        }
      } else {
        delay_key_pressed = false;
      }
      return false;
      break;
    case SYM_ENT:
        process_tap(record->event.pressed, SYM, KC_ENTER);
        return false;
        break;
    case OPT_SPC:
        process_tap(record->event.pressed, OPT, KC_SPACE);
        return false;
        break;
    case NUM_ZKHK:
        process_tap(record->event.pressed, NUM, KC_ZKHK);
        return false;
        break;
    default:
    break;
  }
  return true;
}

uint8_t layer_state_old;

void matrix_scan_user(void) {
  if (delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)) {
    register_delay_code(BASE);
  }

  if (!delay_key_pressed) {
    unregister_delay_code();
  }

  if(layer_state_old != layer_state){
    switch (layer_state) {
      case BASE:
        break;
      case OPT:
        register_delay_code(OPT);
        break;
      case NUM:
        register_delay_code(NUM);
        break;
      case SYM:
        register_delay_code(SYM);
        break;
      case FUNC:
        register_delay_code(FUNC);
        break;
    }
    layer_state_old = layer_state;
  }
}
