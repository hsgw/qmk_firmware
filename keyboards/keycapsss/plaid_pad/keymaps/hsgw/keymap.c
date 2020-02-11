#include QMK_KEYBOARD_H
#include "keymap_jp.h"

enum plaidpad_layers {
    NUMPAD,
    SUB,
    SUB2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[NUMPAD] = LAYOUT_ortho_4x4(
		KC_7, KC_8,    KC_9,      KC_TAB,
		KC_4, KC_5,    KC_6,      KC_BSPC,
		KC_1, KC_2,    KC_3,      KC_SPC,
		KC_0, JP_DOT,  LT(SUB2,JP_YEN),   LT(SUB, KC_ENT)
),

[SUB] = LAYOUT_ortho_4x4(
		KC_ESC,  KC_UP,   JP_YEN,    RSFT(KC_TAB),
		KC_LEFT, KC_DOWN, KC_RIGHT,  KC_DEL,
		JP_PLUS, JP_MINS, JP_ASTR,   _______,
		JP_SLSH, JP_COMM, JP_EQL,   _______
),

[SUB] = LAYOUT_ortho_4x4(
		JP_ZHTG,    XXXXXXX,    XXXXXXX,     XXXXXXX,
		LCTL(KC_C), LCTL(KC_V), LCTL(KC_A),  _______,
		JP_LPRN,    JP_RPRN,    XXXXXXX,     _______,
		XXXXXXX,    XXXXXXX,    LT(SUB2,JP_COMM),     _______
),

};

// Set led state during powerup
void keyboard_post_init_user(void) {
    writePinHigh(LED_GREEN);
}

bool led_update_user(led_t led_state) {
    writePin(LED_RED, led_state.num_lock);
    return true;
}
