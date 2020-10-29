/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0495
#define DEVICE_VER      0x0001
#define MANUFACTURER Dm9Records
#define PRODUCT luan
#define DESCRIPTION arm macro pad for test

// /* key matrix size */
// #define MATRIX_ROWS 5
// #define MATRIX_COLS 12

// #define MATRIX_COL_PINS { A2, A1, A0, F1, F0, C15, C14, C13, B9, A15, A10, A9 }
// #define MATRIX_ROW_PINS { A8, B14, B12, B4, B3 }
// #define DIODE_DIRECTION COL2ROW

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

// #define DIRECT_PINS {{B12, B13}}
// #define DIRECT_PINS_RIGHT {{B12, B13}}

#define MATRIX_COL_PINS {B12, B13}
#define MATRIX_ROW_PINS {B9}
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


/* RGBLED setting */
#define RGBLIGHT_ANIMATIONS

#define WS2812_SPI SPID2
#define RGB_DI_PIN B15
#define RGBLED_NUM 1
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_EXTERNAL_PULLUP

/* Split communication setting */
#define SOFT_SERIAL_PIN B6  // USART TX pin
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: about 460800 baud
                                   //  1: about 230400 baud (default)
                                   //  2: about 115200 baud
                                   //  3: about 57600 baud
                                   //  4: about 38400 baud
                                   //  5: about 19200 baud
#define SERIAL_USART_DRIVER SD1 // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 0 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7

#define SPLIT_USB_DETECT
#define MASTER_LEFT



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
