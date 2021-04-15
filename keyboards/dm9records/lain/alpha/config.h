/*
Copyright 2019 Takuya Urakawa(hsgw), dm9records.com, 5z6p.com

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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x1998
#define DEVICE_VER 0x0001
#define MANUFACTURER Dm9 Records
#define PRODUCT lain
#define DESCRIPTION ergonomic 40 % keyboard

#define USB_MAX_POWER_CONSUMPTION 100

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/*
 * Keyboard Matrix Assignments
 */
// clang-format off
#define DIRECT_PINS {\
    {B14,   D8,     D9, D12,D13,C8, C9,    A15,C10,C11,C12,D0, D1},\
    {B12,   B13,    B15,D10,D11,C6, C7,    D2, D3, D4, D6, B4, B7},\
    {NO_PIN,A5,     A6, A7, C4, C5, B0,    E2, E3, E4, E5, E6,C13},\
    {NO_PIN,NO_PIN, A2, A1, A0, F3, C3,    F1, F0,F10, F9,C15,C14}\
}
// clang-format on
// #define DIODE_DIRECTION COL2ROW

/*
 * LED indicator
 */
#define LED_NUM 3
#define LED_PINS \
    { C2, C1, C0 }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
