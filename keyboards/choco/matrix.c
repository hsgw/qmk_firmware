/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar
Modified: 2019 Takuya Urakawa(hsgw), dm9records.com, 5z6p.com

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
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

#if (MATRIX_COLS <= 8)
#  define print_matrix_header() print("\nr/c 01234567\n")
#  define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#  define matrix_bitpop(i) bitpop(matrix[i])
#  define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#  define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
#  define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
#  define matrix_bitpop(i) bitpop16(matrix[i])
#  define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#  define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#  define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
#  define matrix_bitpop(i) bitpop32(matrix[i])
#  define ROW_SHIFTER ((uint32_t)1)
#endif

#ifdef MATRIX_MASKED
extern const matrix_row_t matrix_mask[];
#endif

static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

__attribute__((weak)) void matrix_init_quantum(void) { matrix_init_kb(); }

__attribute__((weak)) void matrix_scan_quantum(void) { matrix_scan_kb(); }

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

// Deprecated.
bool matrix_is_modified(void) {
  if (debounce_active()) return false;
  return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) {
  // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
  // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
  return matrix[row] & matrix_mask[row];
#else
  return matrix[row];
#endif
}

void matrix_print(void) {
  print_matrix_header();

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row);
    print(": ");
    print_matrix_row(row);
    print("\n");
  }
}

uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += matrix_bitpop(i);
  }
  return count;
}

static void init_pins(void) {
  for (int row = 0; row < MATRIX_ROWS; row++) {
    for (int col = 0; col < MATRIX_COLS; col++) {
      pin_t pin = direct_pins[row][col];
      if (pin != NO_PIN) {
        setPinInputHigh(pin);
      }
    }
  }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
  matrix_row_t last_row_value = current_matrix[current_row];
  current_matrix[current_row] = 0;

  for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
    pin_t pin = direct_pins[current_row][col_index];
    if (pin != NO_PIN) {
      current_matrix[current_row] |= readPin(pin) ? 0 : (ROW_SHIFTER << col_index);
    }
  }

  current_matrix[0] ^= 1U << BOOT_SW_POS;

  return (last_row_value != current_matrix[current_row]);
}

void matrix_init(void) {
  // initialize key pins
  init_pins();
  // BOOT SW has external pulldown resisotor
  palSetLineMode(BOOT_SW_LINE, PAL_MODE_INPUT);

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    raw_matrix[i] = 0;
    matrix[i]     = 0;
  }

  debounce_init(MATRIX_ROWS);

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  bool changed = false;

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
  // Set row, read cols
  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    changed |= read_cols_on_row(raw_matrix, current_row);
  }
#elif (DIODE_DIRECTION == ROW2COL)
  // Set col, read rows
  for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
    changed |= read_rows_on_col(raw_matrix, current_col);
  }
#endif

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_quantum();
  return 1;
}
