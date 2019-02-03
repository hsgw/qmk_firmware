#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#define JA_CLON KC_QUOT  // : and +
#define JA_AT   KC_LBRC  // @ and `
#define JA_HAT  KC_EQL   // ^ and ~
#define JA_ENUN KC_RO    // \ and _ (EN mark and UNder score)
#define JA_ENVL KC_JYEN  // \ and | (EN mark and Vertical Line)
#define JA_LBRC KC_RBRC  // [ and {
#define JA_RBRC KC_BSLS  // ] and }

enum LAYER_NO {
  BASE = 0,
  NUM,
  META,
  CONF
};

enum CUSTOM_KEYCODES {
  RGB_RST = SAFE_RANGE,
  RGB_TYPE,
};

enum TAP_DANCE_KEYCODES {
  TD_LBRT,
  TD_RBRT,
  TD_SC,
  TD_NUM,
  TD_META,
  TD_DASH
};

// Fillers to make layering more clear
#define ______ KC_TRNS
#define XXXXXX KC_NO
#define META_ZK LT(META,KC_ZKHK)
#define META_BS LT(META, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT( \
    XXXXXX,  KC_M,   KC_L,  KC_SLSH,    XXXXXX,  XXXXXX,  XXXXXX,                   XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,   XXXXXX,  XXXXXX,  XXXXXX, \
    XXXXXX,  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    JA_AT,    XXXXXX, \
    KC_LCTL,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, JA_CLON,  XXXXXX, \
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RO,    XXXXXX, \
                               KC_LALT, KC_LGUI, META_ZK, TD(TD_NUM), KC_SPC,  KC_ENT, KC_BSPC, TD(TD_META), KC_RGUI,   KC_RALT \
  ),

  [NUM] = LAYOUT( \
    XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,                   XXXXXX, XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,   XXXXXX, \
    XXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                     KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, JA_HAT,   XXXXXX, \
    ______,           LSFT(KC_2),LSFT(KC_3),LSFT(KC_4),LSFT(KC_5),LSFT(KC_6),LSFT(KC_7),LSFT(KC_8),LSFT(KC_9),KC_MINS,LSFT(KC_MINS),LSFT(JA_HAT),XXXXXX, \
    ______,           LSFT(KC_1),______,  ______,  ______,  ______,                 KC_JYEN, LSFT(KC_JYEN),  ______,  ______,  ______,  ______,  XXXXXX, \
                               ______, ______, ______, ______, ______,  ______, ______, ______, ______,   ______ \
  ),

  [META] = LAYOUT( \
    MO(CONF),  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,                    XXXXXX, XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,   XXXXXX,  \
    XXXXXX,    KC_DEL,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, \
    ______,             KC_TAB,  TD(TD_DASH),  ______,   TD(TD_LBRT), TD(TD_RBRT),           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS, KC_HOME, KC_END, \
    ______,             KC_F1,  ______,  ______,  ______,  ______,                    ______,  ______,  ______,  ______,  KC_SLCK, KC_PGUP, KC_PGDN, \
                                 ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______ \
  ),

 [CONF] = LAYOUT( \
    ______,  RGB_TYPE,RGB_MOD,  RGB_VAI, RGB_HUI, RGB_HUI,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, \
    RGB_RST, RGB_TOG, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_HUD,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, \
    XXXXXX,           XXXXXX,   XXXXXX,  XXXXXX,  XXXXXX,   XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, \
    XXXXXX,           XXXXXX,   XXXXXX,  XXXXXX,  XXXXXX,   XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX, \
                      XXXXXX,   XXXXXX,  XXXXXX,  XXXXXX,   XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX,  XXXXXX \
  )
};

bool enableLEDTypeAnime = false;


void matrix_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            enableLEDTypeAnime = false;
            rgblight_step();
          }
      #endif
      return false;
    case RGB_TYPE:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          enableLEDTypeAnime = !enableLEDTypeAnime;
        }
      #endif
      return false;
    default:
      break;
  }
  #ifdef RGBLIGHT_ENABLE
    if(enableLEDTypeAnime) {
      rgblight_mode_noeeprom(1);
      uint16_t hue = (rgblight_config.hue + 5) % 360;
      rgblight_sethsv_noeeprom(hue, rgblight_config.sat, rgblight_config.val);
    }
  #endif
    return true;
}

void td_lbrt_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      register_code(KC_RSFT);
      register_code(KC_8);
      break;
    case 2:
      register_code(JA_LBRC);
      break;
    case 3:
      register_code(KC_RSFT);
      register_code(JA_LBRC);
      break;
    default:
      break;
  }
}

void td_lbrt_reset(qk_tap_dance_state_t *state, void *user_data){
  switch (state->count) {
    case 1:
      unregister_code(KC_RSFT);
      unregister_code(KC_8);
      break;
    case 2:
      unregister_code(JA_LBRC);
      break;
    case 3:
      unregister_code(KC_RSFT);
      unregister_code(JA_LBRC);
      break;
    default:
      break;
  }
}

void td_rbrt_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      register_code(KC_RSFT);
      register_code(KC_9);
      break;
    case 2:
      register_code(JA_RBRC);
      break;
    case 3:
      register_code(KC_RSFT);
      register_code(JA_RBRC);
      break;
    default:
      break;
  }
}

void td_rbrt_reset(qk_tap_dance_state_t *state, void *user_data){
  switch (state->count) {
    case 1:
      unregister_code(KC_RSFT);
      unregister_code(KC_9);
      break;
    case 2:
      unregister_code(JA_RBRC);
      break;
    case 3:
      unregister_code(KC_RSFT);
      unregister_code(JA_RBRC);
      break;
    default:
      break;
  }
}

void td_num_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      reset_oneshot_layer();
      layer_on(NUM);
      break;
    case 2:
      register_code(KC_RSFT);
      set_oneshot_layer(NUM, ONESHOT_START);
      break;
    default:
      break;
  }
}

void td_num_reset(qk_tap_dance_state_t *state, void *user_data){
  switch (state->count) {
    case 1:
      layer_off(NUM);
      break;
    case 2:
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    default:
      break;
  }
}

void td_meta_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      layer_on(META);
      break;
    case 2:
      register_code(KC_RSFT);
      layer_on(META);
      break;
    default:
      break;
  }
}

void td_meta_reset(qk_tap_dance_state_t *state, void *user_data){
  switch (state->count) {
    case 1:
      layer_off(META);
      break;
    case 2:
      unregister_code(KC_RSFT);
      layer_off(META);
      break;
    default:
      break;
  }
}

void td_dash_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      register_code(KC_RSFT);
      register_code(KC_7);
      break;
    case 2:
      register_code(KC_RSFT);
      register_code(KC_2);
      break;
    case 3:
      register_code(KC_RSFT);
      register_code(JA_AT);
      break;
    case 4:
      register_code(KC_RSFT);
      register_code(JA_AT);
      _delay_ms(10);
      unregister_code(JA_AT);
      _delay_ms(10);
      register_code(JA_AT);
      _delay_ms(10);
      unregister_code(JA_AT);
      _delay_ms(10);
      register_code(JA_AT);
      break;
    default:
      break;
  }
}

void td_dash_reset(qk_tap_dance_state_t *state, void *user_data){
  switch (state->count) {
    case 1:
      unregister_code(KC_RSFT);
      unregister_code(KC_7);
      break;
    case 2:
      unregister_code(KC_RSFT);
      unregister_code(KC_2);
      break;
    case 3:
      unregister_code(KC_RSFT);
      unregister_code(JA_AT);
      break;
    case 4:
      unregister_code(KC_RSFT);
      unregister_code(JA_AT);
      break;
    default:
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LBRT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lbrt_finished, td_lbrt_reset),
  [TD_RBRT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rbrt_finished, td_rbrt_reset),
  [TD_SC] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LCTL),
  [TD_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_num_finished, td_num_reset),
  [TD_META] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_meta_finished, td_meta_reset),
  [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_dash_finished, td_dash_reset)
};
