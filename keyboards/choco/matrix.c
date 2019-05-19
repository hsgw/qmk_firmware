/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"

#ifndef DEBOUNCE
#  define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

void matrix_init(void) {
  palSetPadMode(GPIOB, 8, PAL_MODE_INPUT);
  // palSetGroupMode(GPIOA, GPIOA_MASK, 0, PAL_MODE_INPUT_PULLUP);
  // palSetGroupMode(GPIOC, GPIOC_MASK, 0, PAL_MODE_INPUT_PULLUP);
  // palSetGroupMode(GPIOF, GPIOF_MASK, 0, PAL_MODE_INPUT_PULLUP);

  // debug
  debug_matrix = true;
}

uint8_t matrix_scan(void) {
  // matrix_col_t temp = ((uint32_t)((palReadLine(LINE_BOOT) == PAL_LOW) ? 0 : (1U << 8) | palReadGroup(GPIOB, GPIOB_MASK, 0)) << 16) | palReadGroup(GPIOA, GPIOA_MASK, 0) | palReadGroup(GPIOC, GPIOC_MASK, 0) | palReadGroup(GPIOF, GPIOF_MASK, 0);
  matrix_col_t temp = (palReadPad(GPIOB, 8) == PAL_HIGH) ? (1 << 0) : 0;
  if (matrix_debouncing[0] != temp) {
    matrix_debouncing[0] = temp;
    if (debouncing) {
      debug("bounce!: ");
      debug_hex(debouncing);
      debug("\n");
    }
    debouncing = DEBOUNCE;
  }

  if (debouncing) {
    if (--debouncing) {
      wait_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }

  return 1;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row);
    print(": ");
    pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}
