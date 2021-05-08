/* Copyright 2021 mtei
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
// clang-format off

#include QMK_KEYBOARD_H

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define kc5(a,b,c,d,e) KC_##a, KC_##b, KC_##c, KC_##d, KC_##e
#define kc6(a,b,c,d,e,f) KC_##a, KC_##b, KC_##c, KC_##d, KC_##e, KC_##f

//Macros
#define LT_NUML_SP  LT(_NUML,KC_SPC)
#define LT_NUMR_SP  LT(_NUMR,KC_SPC)
#define LT_RA_BSPC  LT(_RAISE,KC_BSPC)
#define LT_RA_ENT   LT(_RAISE,KC_ENT)
#define ___       _______

enum layer_number {
    _BASE = 0,
    _NUML,
    _NUMR,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    BASE = SAFE_RANGE,
    NUML,
    NUMR,
    xEISU,
    xKANA,
    ZERO2,
    RGBRST
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#define  Q_____W_____E_____R_____T___MINUS  kc6( Q, W, E, R, T, MINUS)
#define PLUS___Y_____U_____I_____O_____P    kc6( PLUS, Y, U, I, O, P )
#define  A_____S_____D_____F_____G___LBRC   kc6( A, S, D, F, G, LBRC )
#define RBRC___H_____J_____K_____L___SCLN   kc6( RBRC, H, J, K, L, SCLN )
#define  Z_____X_____C_____V_____B____GRV   kc6( Z, X, C, V, B, GRV )
#define QUOT___N_____M___COMM___DOT__SLSH   kc6( QUOT, N, M, COMM, DOT, SLSH )
#define LOWER___LOWER__CAPS__LALT__LGUI__NUML__RABS  MO(_LOWER), MO(_LOWER), KC_CAPS, KC_LALT, KC_LGUI, LT_NUML_SP, LT_RA_BSPC
#define RAEN_NUMR__RGUI__RALT___APP_LOWER__LOWER     LT_RA_ENT,  LT_NUMR_SP, KC_RGUI, KC_RALT, KC_APP,  MO(_LOWER), MO(_LOWER)

  /* BASE
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | ESC  |   Q  |   W  |   E  |   R  |   T  |  -   |   |  =   |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |  [   |   |  ]   |   H  |   J  |   K  |   L  |   ;  | Ctrl |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |  `   |   |  '   |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+   |------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  |   | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `------------------------------------------------+   +------------------------------------------------'
   */
  [_BASE] = LAYOUT_wrapper(
     KC_ESC,   Q_____W_____E_____R_____T___MINUS,   PLUS___Y_____U_____I_____O_____P,  KC_BSLS,
     KC_LCTL,  A_____S_____D_____F_____G___LBRC,    RBRC___H_____J_____K_____L___SCLN, KC_RCTL,
     KC_LSFT,  Z_____X_____C_____V_____B____GRV,    QUOT___N_____M___COMM___DOT__SLSH, KC_RSFT,
     LOWER___LOWER__CAPS__LALT__LGUI__NUML__RABS,   RAEN_NUMR__RGUI__RALT___APP_LOWER__LOWER
  ),

  /* Num */
#define EXLM__AT__HASH___DLR__PERC  kc5( EXLM, AT,   HASH, DLR,  PERC )
#define CIRC_AMPR_ASTR__LPRN__RPRN  kc5( CIRC, AMPR, ASTR, LPRN, RPRN )
#define _1_____2_____3_____4_____5  kc5( 1,    2,    3,    4,    5 )
#define _6_____7_____8_____9_____0  kc5( 6,    7,    8,    9,    0 )
#define F1____F2____F3____F4____F5  kc5( F1,  F2,   F3,   F4,    F5 )
#define F6____F7____F8____F9___F10  kc5( F6,  F7,   F8,   F9,    F10 )
#define ____z_____z_____z_____z      _______, _______, _______, _______
#define ____z_____z_____z            _______, _______, _______
#define ____z_____z                  _______, _______
  /* ,------------------------------------------------.      ,------------------------------------------------.
   * |      |   !  |   @  |   #  |   $  |   %  |      |      |      |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |      |      |      |   6  |   7  |   8  |   9  |   0  | F12  |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------+------+      |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `------------------------------------------------+      +------------------------------------------------'
   */
  [_NUML] = LAYOUT_wrapper(
    _______,   EXLM__AT__HASH___DLR__PERC, ____z_____z,   CIRC_AMPR_ASTR__LPRN__RPRN,  _______,
    _______,   _1_____2_____3_____4_____5, ____z_____z,   _6_____7_____8_____9_____0,  KC_F12,
    _______,   F1____F2____F3____F4____F5, ____z_____z,   F6____F7____F8____F9___F10,  KC_F11,
    _______, ____z_____z_____z_____z,____z_____z_____z,KC_SPC, ____z_____z_____z_____z, _______
   ),
  [_NUMR] = LAYOUT_wrapper(
    _______,   EXLM__AT__HASH___DLR__PERC, ____z_____z,   CIRC_AMPR_ASTR__LPRN__RPRN,  _______,
    _______,   _1_____2_____3_____4_____5, ____z_____z,   _6_____7_____8_____9_____0,  KC_F12,
    _______,   F1____F2____F3____F4____F5, ____z_____z,   F6____F7____F8____F9___F10,  KC_F11,
    _______, ____z_____z_____z_____z,KC_SPC, ____z_____z_____z,____z_____z_____z_____z, _______
   ),
  
  /* Lower */
#define XXXX__PAUS__SLCK___INS__XXXX   XXXXXXX, KC_PAUS, KC_SLCK, KC_INS,  XXXXXXX
#define XXXX___INS__SLCK__PAUS__XXXX   XXXXXXX, KC_INS,  KC_SLCK, KC_PAUS, XXXXXXX
#define HOME__XXXX____UP___DEL__PGUP   KC_HOME, XXXXXXX, KC_UP,   KC_DEL,  KC_PGUP
#define PGUP___DEL____UP__XXXX__HOME   KC_PGUP, KC_DEL,  KC_UP,   XXXXXXX, KC_HOME
#define END___LEFT__DOWN__RGHT__PGDN   kc5( END,  LEFT,  DOWN,    RGHT,    PGDN )
#define PGDN__LEFT__DOWN__RGHT___END   kc5( PGDN, LEFT,  DOWN,    RGHT,    END )
#define ______PSCR__________________   _______, KC_PSCR, _______, _______, _______
#define __________________PSCR______   _______, _______, _______, KC_PSCR, _______
#define ADJ___ADJ  MO(_ADJUST), MO(_ADJUST)
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Home |      | Up   |Delete| PgUp |             | PgUp |Delete| Up   |      | Home |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | End  | Left | Down | Right| PgDn |             | PgDn | Left | Down | Right| End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |Adjust|Adjust|      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_wrapper(
    XXXXXXX, XXXX__PAUS__SLCK___INS__XXXX, ____z_____z, XXXX___INS__SLCK__PAUS__XXXX, _______,
    _______, HOME__XXXX____UP___DEL__PGUP, ____z_____z, PGUP___DEL____UP__XXXX__HOME, _______,
    _______, END___LEFT__DOWN__RGHT__PGDN, ____z_____z, PGDN__LEFT__DOWN__RGHT___END, _______,
    _______, ______PSCR__________________,  ADJ___ADJ,  __________________PSCR______, _______
  ),

  /* Raise */
#define XXXX__XXXX__XXXX__UNDS__MINS   XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_MINS
#define  EQL__PLUS__XXXX__XXXX__XXXX   KC_EQL,  KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX
#define XXXX__XXXX__XXXX__LCBR__LBRC   XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC
#define RBRC__RCBR__XXXX__XXXX__XXXX   KC_RBRC, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX
#define XXXX__XXXX__XXXX__TILD___GRV   XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD,  KC_GRV
#define QUOT___DQT__XXXX__XXXX__XXXX   KC_QUOT, KC_DQT,  XXXXXXX, XXXXXXX, XXXXXXX
#define XXXX______________XXXX         XXXXXXX, _______, _______, XXXXXXX
  /* ,-----------------------------------------.             ,-----------------------------------------.
   * | TAB  |      |      |      |  _   |  -   |             |  =   |  +   |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | EISU |      |      |      |  {   |  [   |             |  ]   |  }   |      |      |      | KANA |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  ~   |  `   |             |  '   |   "  |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_wrapper(
     KC_TAB, XXXX__XXXX__XXXX__UNDS__MINS, ____z_____z, EQL__PLUS__XXXX__XXXX__XXXX, XXXXXXX,
      xEISU, XXXX__XXXX__XXXX__LCBR__LBRC, ____z_____z, RBRC__RCBR__XXXX__XXXX__XXXX, xKANA,
    XXXXXXX, XXXX__XXXX__XXXX__TILD___GRV, ____z_____z, QUOT___DQT__XXXX__XXXX__XXXX, XXXXXXX,
        ADJ___ADJ, XXXX______________XXXX, ____z_____z, XXXX______________XXXX,  ADJ___ADJ
  ),

    /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
    XXXXXXX, RESET,   RGBRST,  RGB_TOG,   AU_ON, AG_SWAP, ___,___, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM, ___,___, AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, ___,___, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ___,___, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______ \
   )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case xEISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case xKANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

// clang-format on
