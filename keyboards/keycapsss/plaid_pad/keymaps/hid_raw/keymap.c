#include QMK_KEYBOARD_H
#include "raw_hid.h"

static uint8_t rawdata[8];

enum custom_keycodes {
  HID_S = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,-----------------------,
 * |  7  |  8  |  9  |  /  |
 * |-----+-----+-----+-----|
 * |  4  |  5  |  6  |  *  |
 * |-----+-----+-----+-----|
 * |  1  |  2  |  3  |  -  |
 * |-----+-----+-----+-----|
 * |  0  |  .  |  =  |  +  |
 * `-----------------------'
 */
LAYOUT_ortho_4x4(
		HID_S, KC_P8,   KC_P9,      KC_PSLS,
		KC_P4, KC_P5,   KC_P6,      KC_PAST,
		KC_P1, KC_P2,   KC_P3,      KC_PMNS,
		S(KC_CAPS), KC_PDOT, KC_PEQL,    KC_PPLS
)

};

// Set led state during powerup
void keyboard_post_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case HID_S:
        if (record->event.pressed) {
            raw_hid_send(rawdata, 8);
        }
        return false;
        break;
    default:
        break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {         // First encoder - top left
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  } else if (index == 1) {  // Second encoder - top right
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    for(int i=0; i<8;i++) {
        rawdata[i] = data[i];
    }
}
