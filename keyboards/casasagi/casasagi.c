/* Copyright 2021 SMKiJ Casasagi Contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "casasagi.h"

#ifdef RGB_MATRIX_ENABLE

#    define MPOSL(ROW, COL) \
        { (COL * 17), (ROW * 21) }
#    define MPOSR(ROW, COL) \
        { ((COL + 7) * 17), (ROW * 21) }

// clang-format off
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 2,  1,  0, 27, 26, 25, 24},
        { 3,  4,  5, 20, 21, 22, 23},
        { 8,  7,  6, 19, 18, 17, 16},
        { 9, 10, 11, 12, 13, 14, 15},
        {31, 30, 29, 28, 55, 54, 53},
        {32, 33, 34, 35, 50, 51, 52},
        {39, 38, 37, 36, 49, 48, 47},
        {40, 41, 42, 43, 44, 45, 46}
    }, {
        // LED Index to Physical Position
        MPOSL( 0, 2), MPOSL( 0, 1), MPOSL( 0, 0),
        MPOSL( 1, 0), MPOSL( 1, 1), MPOSL( 1, 2),
        MPOSL( 2, 2), MPOSL( 2, 1), MPOSL( 2, 0),
        MPOSL( 3, 0), MPOSL( 3, 1), MPOSL( 3, 2), MPOSL( 3, 3), MPOSL( 3, 4), MPOSL( 3, 5), MPOSL( 3, 6),
        MPOSL( 2, 6), MPOSL( 2, 5), MPOSL( 2, 4), MPOSL( 2, 3),
        MPOSL( 1, 3), MPOSL( 1, 4), MPOSL( 1, 5), MPOSL( 1, 6),
        MPOSL( 0, 6), MPOSL( 0, 5), MPOSL( 0, 4), MPOSL( 0, 3),

        MPOSR( 0, 3), MPOSR( 0, 2), MPOSR( 0, 1), MPOSR( 0, 0),
        MPOSR( 1, 0), MPOSR( 1, 1), MPOSR( 1, 2), MPOSR( 1, 3),
        MPOSR( 2, 3), MPOSR( 2, 2), MPOSR( 2, 1), MPOSR( 2, 0),
        MPOSR( 3, 0), MPOSR( 3, 1), MPOSR( 3, 2), MPOSR( 3, 3), MPOSR( 3, 4), MPOSR( 3, 5), MPOSR( 3, 6),
        MPOSR( 2, 6), MPOSR( 2, 5), MPOSR( 2, 4),
        MPOSR( 1, 4), MPOSR( 1, 5), MPOSR( 1, 6),
        MPOSR( 0, 6), MPOSR( 0, 5), MPOSR( 0, 4),
    }, {
        // LED Index to Flag
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,
        LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL,LED_FLAG_ALL
    }
};
// clang-format on
#endif

void board_init(void) {
    // remap dma channel for SPI2
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_SPI2_DMA_RMP;

    setPinInputHigh(SPLIT_HAND_PIN);
}

bool is_keyboard_left(void) { return readPin(SPLIT_HAND_PIN); }
