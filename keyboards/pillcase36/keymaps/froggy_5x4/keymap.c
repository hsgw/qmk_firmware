#include "pillcase36.h"
#include "print.h"

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _OPT 1
#define _FUNC 2
#define _SYM 3
#define _NUM 4
#define _MOD 5

#define L_BASE 0
#define L_OPT 1
#define L_FUNC 2
#define L_SYM 3
#define L_NUM 4
#define L_MOD 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EISU,
  KANA,
  RGBRST,
  RGBOFF,
  RGB1,
  RGB2,
  RGB3,
  OPT_TAP_SP,
  DESKTOP,
  MAC,
  WIN,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,----------------------------------.
   * |   P  |   K  |   R  |   A  |   F  |
   * |------+------+------+------+------|
   * |   D  |   T  |   H  |   E  |   O  |
   * |------+------+------+------+------|
   * |   Y  |   S  |   N  |   I  |   U  |
   * |------+------+------+------+------|
   * | MOD  | Shift| Sym  | Num  | OPT  |
   * `----------------------------------'
   */
  [_BASE] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,    KC_SCLN,       KC_LBRC,       KC_LPRN,       KC_LT,         KC_LCBR,\
      XXXXXXX,    KC_P,          KC_K,          KC_R,          KC_A,          KC_F,\
      XXXXXXX,    KC_D,          KC_T,          KC_H,          KC_E,          KC_O,\
      XXXXXXX,    KC_Y,          KC_S,          KC_N,          KC_I,          KC_U,\
      XXXXXXX,    MO(_MOD),      OSM(MOD_LSFT), MO(_SYM),      MO(_NUM),      MO(_OPT)\
      ),

  /* Opt
   * ,----------------------------------.
   * |   J  |   M  |   B  |   '  |  .   |
   * |------+------+------+------+------|
   * |   V  |   C  |   L  |   Z  |  Q   |
   * |------+------+------+------+------|
   * |   X  |   G  |   W  |   -  |  ,   |
   * |------+------+------+------+------|
   * | Ctrl | Shift| ALT  |      |      |
   * `----------------------------------'
   */
  [_OPT] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_J,         KC_M,         KC_B,         KC_QUOT,   KC_DOT, \
      XXXXXXX, KC_V,         KC_C,         KC_L,         KC_Z,      KC_Q, \
      XXXXXXX, KC_X,         KC_G,         KC_W,         KC_MINUS,  KC_COMMA,\
      XXXXXXX, OSM(MOD_LCTL),OSM(MOD_LSFT),OSM(MOD_LALT), _______,   _______\
      ),

  /* _MOD
   * ,----------------------------------.
   * |   a  |      |      |      |      |
   * |------+------+------+------+------|
   * |   ;  |   [  |   (  |   <  |   {  |
   * |------+------+------+------+------|
   * | Shift| Ctrl | ALT  | TAB  | Enter|
   * |------+------+------+------+------|
   * |      | ESC  | ZKHK |  BS  | SPACE|
   * `----------------------------------'
   */
  [_MOD] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX,    KC_A,       _______,       _______,       _______,       _______,\
      XXXXXXX,    KC_SCLN,       KC_LBRC,       KC_LPRN,       KC_LT,         KC_LCBR,\
      XXXXXXX,    OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), KC_TAB,        KC_ENT,\
      XXXXXXX,    _______,       LALT(KC_ZKHK), KC_BSPC,       KC_SPC,        KC_ENT\
      ),

  /* Func
   * ,----------------------------------.
   * |  F9  |  F10 |  F11 | F12  |      |
   * |------+------+------+------+------|
   * |  F5  |  F6  |  F7  | F8   |      |
   * |------+------+------+------+------|
   * |  F1  |  F2  |  F3  | F4   |      |
   * |------+------+------+------+------|
   * |      |      |      |      |      |
   * `----------------------------------'
   */
  [_FUNC] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET, \
      XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   MAC,\
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   WIN,\
      XXXXXXX, _______, _______, _______, _______, _______\
      ),

  /* Sym
   * ,-----------------------------------------.
   * |  Ins |  GRV |      |  PU  |  PD  |   ^  |
   * |------+------+------+------+------+------|
   * |      |   \  |   #  |   =  |   ?  |   %  |
   * |------+------+------+------+------+------|
   * |      |   $  |  upA |   @  |   !  |   |  |
   * |------+------+------+------+------+------|
   * |  CL  |  <-  |  dwA |  ->  |   _  |   &  |
   * |------+------+------+------+------+------|
   * |      |      |  PS  |      |   ~  |      |
   * `-----------------------------------------'
   */
  [_SYM] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC, \
      _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC, \
      _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE, \
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR, \
      _______, _______, KC_PSCR, _______, KC_TILD, _______\
      ),

  /* Num
   * ,----------------------------------.
   * |   7  |  8   |  9   |  -   |  /   |
   * |------+------+------+------+------|
   * |   4  |  5   |  6   |  +   |  *   |
   * |------+------+------+------+------|
   * |  1   |  2   |  3   | BSPC | ENTER|
   * |------+------+------+------+------|
   * |  0   |  .   |  .   |      | TAB  |
   * `----------------------------------'
   */
  [_NUM] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_MINS, KC_SLSH,\
      XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_ASTR,\
      XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_BSPC, KC_ENTER, \
      XXXXXXX, KC_P0,   KC_PDOT, KC_COMMA,_______, KC_TAB\
      )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case MAC:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = false;
        keymap_config.swap_ralt_rgui = false;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_norm_song);
        #endif
      }
      break;
    case WIN:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = true;
        keymap_config.swap_ralt_rgui = true;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_swap_song);
        #endif
      }
      break;
    }
  return true;
}


//keyboard start-up code. Runs once when the firmware starts up.
void matrix_init_user(void) {

}

//runs every scan cycle (a lot)
void matrix_scan_user(void) {
}
