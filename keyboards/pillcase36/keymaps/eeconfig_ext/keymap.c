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

#include "print.h"
#include "eeprom.h"
#include "eeprom_ext.h"

enum custom_keycode {
  CK_DBG = SAFE_RANGE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( \
    CK_DBG,    KC_F2,     KC_F3,     KC_F4,   KC_F5,   KC_F6, \
    KC_F7,    KC_F8,     KC_F9,     KC_F10,  KC_F11,  KC_F12, \
    KC_KP_7,  KC_KP_8,   KC_KP_9,   KC_INS,  KC_PSCR, KC_NLCK, \
    KC_KP_4,  KC_KP_5,   KC_KP_6,   KC_BSPC, KC_DEL,  KC_ESC, \
    KC_KP_1,  KC_KP_2,   KC_KP_3,   KC_ENT,  KC_UP,   KC_APP, \
    KC_KP_0,  KC_KP_0,   KC_KP_DOT, KC_LEFT, KC_DOWN, KC_RGHT \
  )
};

void matrix_init_user(void) {
}

void printArray(uint8_t* array, uint16_t length) {
  for(int i=0; i<length;i++) {
    printf("%d ", array[i]);
  }
  print("\n");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CK_DBG:
      if (record->event.pressed) {
        uint16_t read16 = eeprom_read_word((const uint16_t *)0);
        printf("eeconfig magic: 0x%x\n", read16);
        uint8_t read8 = eeconfig_read_debug();
        printf("debug: 0x%x\n", read8);
        read8 = eeconfig_read_default_layer();
        printf("layer: 0x%x\n", read8);
        read8 = eeconfig_read_keymap();
        printf("keymap: 0x%x\n", read8);
        // uint8_t temp[12];
        // EEPROM_read(0, temp, 12);
        // printArray(temp, 12);
      }
      return false;
    default:
      return true;
  }
}
