#include QMK_KEYBOARD_H

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
  META
};

enum TAP_DANCE_KEYCODES {
  TD_LBRT,
  TD_RBRT,
  TD_SC,
  TD_NUM
};

// Fillers to make layering more clear
#define ______ KC_TRNS
#define XXXXXX KC_NO
#define META_ZK LT(META,KC_ZKHK)
#define META_BS LT(META, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_plaid_grid( \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JA_AT,    \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,       KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JA_CLON,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RO,    \
    KC_TAB,  KC_LGUI, KC_LALT, META_ZK, TD(TD_NUM), KC_SPC,  KC_ENT,  KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [NUM] = LAYOUT_plaid_grid( \
    KC_DEL,  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,     KC_MINS,\
    ______,  LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), KC_MINS,  LSFT(KC_MINS),\
    ______,  ______,     ______,     ______,     ______,     TD(TD_LBRT),TD(TD_RBRT),______,     JA_LBRC,    JA_RBRC,    JA_HAT,   KC_JYEN, \
    ______,  ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,   ______\
  ),

  [META] = LAYOUT_plaid_grid( \
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
    ______,  ______,  ______,  ______,  KC_INS,  KC_PSCR,     KC_LEFT,     KC_DOWN, KC_UP,   KC_RGHT, ______,  KC_F12, \
    ______,  ______,  ______,  ______,  ______,  TD(TD_LBRT), TD(TD_RBRT), ______,  JA_LBRC, JA_RBRC, KC_SLCK, ______, \
    ______,  ______,  ______,  ______,  ______,  ______,      ______,      ______,  KC_HOME, KC_PGDN,  KC_PGUP, KC_END \
  )
};


void matrix_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    default:
      break;
  }
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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LBRT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lbrt_finished, td_lbrt_reset),
  [TD_RBRT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rbrt_finished, td_rbrt_reset),
  [TD_SC] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_LCTL),
  [TD_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_num_finished, td_num_reset),
};
