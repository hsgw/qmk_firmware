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
#include "matrix.h"
#include "wait.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void)
{
  // initialize input
  palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOB, 8, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 3, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_PULLUP);

  // initialize matrix state: all keys off
  matrix[0] = 0;
  matrix_debouncing[0] = 0;

  matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
  matrix_row_t cols = ((palReadPad(GPIOA,5)==PAL_HIGH) ? 0 : (1<<0))
                    | ((palReadPad(GPIOB,8)==PAL_LOW) ? 0 : (1<<1))
                    | ((palReadPad(GPIOA,3)==PAL_HIGH) ? 0 : (1<<2))
                    | ((palReadPad(GPIOA,4)==PAL_HIGH) ? 0 : (1<<3));

  if (matrix_debouncing[0] != cols) {
      matrix_debouncing[0] = cols;
      // if (debouncing) {
      //     debug("bounce!: "); debug_hex(debouncing); debug("\n");
      // }
      debouncing = DEBOUNCE;
  }

  if (debouncing) {
      if (--debouncing) {
          wait_ms(1);
      } else {
          matrix[0] = matrix_debouncing[0];
      }
  }

  matrix_scan_quantum();
  return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    // print("\nr/c 0123456789ABCDEF\n");
    // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //     phex(row); print(": ");
    //     pbin_reverse16(matrix_get_row(row));
    //     print("\n");
    // }
}
