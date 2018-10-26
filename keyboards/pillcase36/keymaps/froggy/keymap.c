#include "pillcase36.h"

extern keymap_config_t keymap_config;

extern uint8_t is_master;

#define DELAY_TIME  75
static uint16_t key_timer;
static uint16_t tap_timer;
static uint16_t delay_registered_code;
static uint8_t delay_mat_row;
static uint8_t delay_mat_col;
static bool delay_key_stat;
static bool delay_key_pressed;
static bool tapping_key;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _OPT 1
#define _FUNC 2
#define _SYM 3
#define _NUM 4

#define L_BASE 0
#define L_OPT 1
#define L_FUNC 2
#define L_SYM 3
#define L_NUM 4

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
   * ,-----------------------------------------.
   * |  C+z |   ;  |   [  |   (  |   <  |   {  |
   * |------+------+------+------+------+------|
   * | KANA |   P  |   K  |   R  |   A  |   F  |
   * |------+------+------+------+------+------|
   * |  BS  |   D  |   T  |   H  |   E  |   O  |
   * |------+------+------+------+------+------|
   * | Shift|   Y  |   S  |   N  |   I  |   U  |
   * |------+------+------+------+------+------|
   * | Ctrl | Alt  | Gui  | Sym  | Num  | OPT  |
   * |------+------+------+------+------+------|
   * |      |      |      | BSPC | SPC  | ENT  |
   * `-----------------------------------------'
   */
  [_BASE] = LAYOUT( \
      LCTL(KC_Z),    KC_SCLN,       KC_LBRC,       KC_LPRN,       KC_LT,         KC_LCBR,\
      KC_TAB,        KC_P,          KC_K,          KC_R,          KC_A,          KC_F,\
      KC_ZKHK,       KC_D,          KC_T,          KC_H,          KC_E,          KC_O,\
      OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,          KC_I,          KC_U,\
      OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), MO(_SYM),      MO(_NUM),      MO(_OPT),\
      ),

  /* Opt
   * ,-----------------------------------------.
   * |  Esc |  :   |  ]   |  )   |  >   |  }   |
   * |------+------+------+------+------+------|
   * |  DEL |   J  |   M  |   B  |   '  |  .   |
   * |------+------+------+------+------+------|
   * |   .  |   V  |   C  |   L  |   Z  |  Q   |
   * |------+------+------+------+------+------|
   * |      |   X  |   G  |   W  |   -  |  ,   |
   * |------+------+------+------+------+------|
   * | Ctrl | Alt  | Gui  | Sym  | Num  | OPT  |
   * |------+------+------+------+------+------|
   * |      |      |      | BSPC | SPC  | ENT  |
   * `-----------------------------------------'
   */
  [_OPT] = LAYOUT( \
      KC_ESC,  KC_COLN,KC_RBRC, KC_RPRN, KC_GT,     KC_RCBR,\
      KC_DEL,  KC_J,   KC_M,    KC_B,    KC_QUOT,   KC_DOT, \
      _______, KC_V,   KC_C,    KC_L,    KC_Z,      KC_Q, \
      _______, KC_X,   KC_G,    KC_W,    KC_MINUS,  KC_COMMA,\
      _______, _______,_______, _______, _______,   _______, \
      _______, _______,_______, _______, _______,   _______\
      ),

  /* Func
   * ,-----------------------------------------.
   * |RGBRST|  Hue |      |  RST |  Mac |  Win |
   * |------+------+------+------+------+------|
   * | RGB1 | VAL+ |  F7  |  F8  |  F9  |      |
   * |------+------+------+------+------+------|
   * | RGB2 | VAL- |  F4  |  F5  |  F6  | F12  |
   * |------+------+------+------+------+------|
   * | RGB3 |  F10 |  F1  |  F2  |  F3  | F11  |
   * |------+------+------+------+------+------|
   * |RGBOFF|      |      |      |      |      |
   * |------+------+------+------+------+------|
   * |      |      |      | BSPC | SPC  | ENT  |
   * `-----------------------------------------'
   */
  [_FUNC] = LAYOUT( \
      RGBRST,RGB_HUI, _______, RESET,   MAC,     WIN,    \
      RGB1,  RGB_VAI, KC_F7,   KC_F8,   KC_F9,   _______,\
      RGB2,  RGB_VAD, KC_F4,   KC_F5,   KC_F6,   KC_F12,\
      RGB3,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,\
      RGBOFF,_______, _______, _______, _______, _______,\
      _______, _______,_______, _______, _______,   _______\
      ),

  /* Sym
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  Ins |  GRV |      |  PU  |  PD  |   ^  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   \  |   #  |   =  |   ?  |   %  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   $  |  upA |   @  |   !  |   |  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  CL  |  <-  |  dwA |  ->  |   _  |   &  |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  PS  |      |   ~  |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_SYM] = LAYOUT( \
      KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC, \
      _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC, \
      _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE, \
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR, \
      _______, _______, KC_PSCR, _______, KC_TILD, _______, \
      _______, _______,_______, _______, _______,   _______\
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      | Func | home |  End |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   *  |  7   |  8   |  9   |  -   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  .   |   /  |  4   |  5   |  6   |  +   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  LN  |  0   |  1   |  2   |  3   |C+S+F1|      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |  ,   |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUM] = LAYOUT( \
      _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______, \
      _______,  KC_ASTR, KC_P7,      KC_P8,   KC_P9,   KC_MINS, \
      KC_PDOT,  KC_SLSH, KC_P4,      KC_P5,   KC_P6,   KC_PLUS, \
      KC_NLCK,  KC_P0,   KC_P1,      KC_P2,   KC_P3,   LCTL(S(KC_F1)), \
      _______,  _______, KC_PDOT,    KC_COMM, _______, _______,\
      _______, _______,_______, _______, _______,   _______\
      )
};

// define variables for reactive RGB
//bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( pgm_read_word(&(keymaps[_BASE][i][j]))==keycode){
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
    if (code & QK_LSFT){
      register_code(KC_LSFT);
    }
    if (code & QK_LCTL){
      register_code(KC_LCTL);
    }
    if (code & QK_LALT){
      register_code(KC_LALT);
    }
    if (code & QK_LGUI){
      register_code(KC_LGUI);
    }
    register_code(code);
    delay_registered_code = code;
    delay_key_stat = false;
    tapping_key = true;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(tap_timer&&keycode!=OPT_TAP_SP){
    tapping_key = true;
  }

  if(keycode==delay_registered_code){
      if (!record->event.pressed){
        unregister_delay_code();
      }
  }

  switch (keycode) {
    case KC_SCLN:
    case KC_LBRC:
    case KC_LPRN:
    case KC_LT:
    case KC_LCBR:
    case KC_P:
    case KC_K:
    case KC_R:
    case KC_A:
    case KC_F:
    case KC_BSPC:
    case KC_D:
    case KC_T:
    case KC_H:
    case KC_E:
    case KC_O:
    case KC_Y:
    case KC_S:
    case KC_N:
    case KC_I:
    case KC_U:
    case LCTL(KC_Z):
    case KC_SPC:
      if (record->event.pressed) {
        register_delay_code(_BASE);
        if(find_mairix(keycode, &delay_mat_row, &delay_mat_col)){
          key_timer = timer_read();
          delay_key_stat = true;
          delay_key_pressed = true;
        }
      }else{
        delay_key_pressed = false;
      }
      return false;
      break;
    case OPT_TAP_SP:
      if (record->event.pressed) {
        tapping_key = false;
        register_delay_code(_OPT);
        layer_on(_OPT);
        tap_timer = timer_read();
      }else{
        layer_off(_OPT);
        if(tapping_key==false && timer_elapsed(tap_timer) < TAPPING_TERM){
          SEND_STRING(" ");
        }
        tap_timer = 0;
      }
      return false;
      break;
   case EISU:
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
    case KANA:
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
    case DESKTOP:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_F11);
        }else{
          SEND_STRING(SS_LGUI("d"));
        }
      } else {
        unregister_code(KC_F11);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
          RGBAnimation = false;
        }
      #endif
      break;
    case RGBOFF:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_disable();
        }
      #endif
      break;
    case RGB1:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB2:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 1);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB3:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_KNIGHT);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
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

uint8_t layer_state_old;

//runs every scan cycle (a lot)
void matrix_scan_user(void) {

  if(delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)){
    register_delay_code(_BASE);
    if(!delay_key_pressed){
      unregister_delay_code();
    }
  }

  if(layer_state_old != layer_state){
    switch (layer_state) {
      case L_BASE:
        break;
      case L_OPT:
        register_delay_code(_OPT);
        break;
      case L_NUM:
        register_delay_code(_NUM);
        break;
      case L_SYM:
        register_delay_code(_SYM);
        break;
      case L_FUNC:
        register_delay_code(_FUNC);
        break;
    }
    layer_state_old = layer_state;
  }
}
