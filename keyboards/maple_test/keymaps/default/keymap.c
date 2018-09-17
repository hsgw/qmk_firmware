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

#include "maple_test.h"
#include "ext_eeprom.h"

#include <print.h>
#include <wait.h>

extern MidiDevice midi_device;

enum custom_keycode {
  CK_DBG = SAFE_RANGE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{CK_DBG}},
};

// uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
// {
//     return KC_A;
// }

void matrix_init_user(void) {
  ext_eeprom_init();
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
        print("debug\n");
        uint16_t address = 0;
        int16_t ret = 0;
        uint8_t data1[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        ret = ext_eeprom_write(address, data1, 16);
        printf("write %d ", ret);
        printf("State: %d error %d\n", I2CD1.state, I2CD1.errors);
        chThdSleepMilliseconds(10);
        uint8_t data2[16] = {0};
        ret = ext_eeprom_read(address, data2, 16);
        printf("read %d ", ret);
        printf("State: %d error %d\n", I2CD1.state, I2CD1.errors);
        printArray(data2, 16);
      }
      return false;
    default:
      return true;
  }
}
