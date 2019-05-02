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

#include QMK_KEYBOARD_H
#include <sendstring_jis.h>
#include "data.h"
#include "control.h"

enum custom_keycodes {
  TETRIS = SAFE_RANGE,
  NKEY,
  NKEY2
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{ TETRIS, TETRIS, TETRIS, TETRIS}}
};

void send_string_fast(const char *str) {
  while(1) {
    char ascii_code = *str;
    if (!ascii_code) break;
    send_char(ascii_code);
    ++str;
  }
}

void send_program(const srccode* code) {
  EDITOR_OPEN();
  send_string_fast(code->name);
  tap_code(KC_ENTER);
  wait_ms(500);
  EDITOR_INPUT();
  send_string_fast(code->code);
  EDITOR_CLOSE();
  wait_ms(500);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case TETRIS:
      if(record->event.pressed) {
        REMOVE_DIR();
        wait_ms(500);
        MAKE_DIR();
        wait_ms(500);
        SEND_STRING("date"SS_TAP(X_ENTER));
        for(uint8_t i=0;i<CODE_NUM;i++) {
          send_program(&code[i]);
        }
        SEND_STRING("date"SS_TAP(X_ENTER));
      }
      return false;
      default:
      break;
  }
  return true;
}
