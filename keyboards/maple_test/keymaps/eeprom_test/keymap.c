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

#include "print.h"
#include "eeprom.h"
#include "eeprom_stm32.h"

enum custom_keycode {
  CK_DBG = SAFE_RANGE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{CK_DBG}},
};

void matrix_init_user(void) {
  if(!eeconfig_is_enabled()){
    eeconfig_init();
  }
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
        uint16_t read;
        uint16_t status = EEPROM_read(0, &read);
        printf("eeconfig magic: 0x%x status:%d\n", read, status);

        status = EEPROM_read(11, &read);
        printf("eeconfig data: 0x%x status:%d\n", read, status);
        status = EEPROM_update(11, read+2);
        printf("eeconfig data write: status:%d\n", status);


        // uint8_t debug_byte = eeconfig_read_debug();
        // printf("eeconfig debug: 0x%x\n", debug_byte);
        // eeconfig_update_debug(debug_byte+1);
      }
      return false;
    default:
      return true;
  }
}
