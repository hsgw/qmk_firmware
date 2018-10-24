/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pillcase36.h"

#include <print.h>

enum custom_keycode {
  CK_DBG = SAFE_RANGE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( \
    KC_F1,    KC_F2,     KC_F3,     KC_F4,   KC_F5,   KC_F6, \
    KC_F7,    KC_F8,     KC_F9,     KC_F10,  KC_F11,  KC_F12, \
    KC_KP_7,  KC_KP_8,   KC_KP_9,   KC_INS,  KC_PSCR, KC_NLCK, \
    KC_KP_4,  KC_KP_5,   KC_KP_6,   KC_BSPC, KC_DEL,  KC_ESC, \
    KC_KP_1,  KC_KP_2,   KC_KP_3,   KC_ENT,  KC_UP,   KC_APP, \
    KC_KP_0,  KC_KP_0,   KC_KP_DOT, KC_LEFT, KC_DOWN, KC_RGHT \
  )
};

// uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
// {
//     return KC_A;
// }

void matrix_init_user(void) {
}

void printArray(uint8_t* array, uint16_t length) {
  for(int i=0; i<length;i++) {
    printf("%d ", array[i]);
  }
  print("\n");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // switch (keycode) {
  //   case CK_DBG:
  //     if (record->event.pressed) {
  //       print("debug\n");
  //       uint16_t address = 0;
  //       int16_t ret = 0;
  //       uint8_t data1[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  //       ret = ext_eeprom_write(address, data1, 16);
  //       printf("write %d ", ret);
  //       printf("State: %d error %d\n", I2CD1.state, I2CD1.errors);
  //       chThdSleepMilliseconds(10);
  //       uint8_t data2[16] = {0};
  //       ret = ext_eeprom_read(address, data2, 16);
  //       printf("read %d ", ret);
  //       printf("State: %d error %d\n", I2CD1.state, I2CD1.errors);
  //       printArray(data2, 16);
  //     }
  //     return false;
  //   default:
  //     return true;
  // }
  return true;
}
