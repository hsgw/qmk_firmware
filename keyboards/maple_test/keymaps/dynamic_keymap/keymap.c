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
#include "flash_keymaps.h"

#include <print.h>
#include <wait.h>

enum custom_keycode {
  CK_DBG = SAFE_RANGE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__((section(".KEYMAPS"))) = {
    {{CK_DBG}},
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
  printf("keymaps address %lx\n", keymaps);
  printf("keycode: %x\n", keycode);
  switch (keycode) {
    case CK_DBG:
      if (record->event.pressed) {
        print("debug\n");
      }
      return false;
    default:
      return true;
  }
}
