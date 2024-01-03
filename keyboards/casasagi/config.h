/*
Copyright 2021 SMKiJ Casasagi Contributors

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
// #define VENDOR_ID 0xFEED
// #define PRODUCT_ID 0x0000
// #define DEVICE_VER 0x0001
// #define MANUFACTURER SMKiJ Casasagi Contributors
// #define PRODUCT casasagi

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 7

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */

#define MATRIX_ROW_PINS \
    { A15, A7, A5, A6 }

#define MATRIX_ROW_PINS_RIGHT \
    { A15, A4, A3, A2 }

#define MATRIX_COL_PINS \
    { B2, B1, B0, B8, B5, B4, B3 }

#define MATRIX_COL_PINS_RIGHT \
    { B2, B1, B0, A7, C13, B9, B8 }

#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* RGBLED setting */
#define WS2812_DI_PIN B15
#define WS2812_SPI_DRIVER SPID2
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_EXTERNAL_PULLUP

#define RGBLED_NUM_LEFT 28
#define RGBLED_NUM_RIGHT 28

#define RGBLED_SPLIT \
    { RGBLED_NUM_LEFT, RGBLED_NUM_RIGHT }
#define RGBLED_NUM (RGBLED_NUM_LEFT + RGBLED_NUM_RIGHT)

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_ANIMATIONS
// clang-format off
#define LED_LAYOUT( \
   L00, L01, L02, L03, L04, L05, L06,   R00, R01, R02, R03, R04, R05, R06, \
   L10, L11, L12, L13, L14, L15, L16,   R10, R11, R12, R13, R14, R15, R16, \
   L20, L21, L22, L23, L24, L25, L26,   R20, R21, R22, R23, R24, R25, R26, \
   L30, L31, L32, L33, L34, L35, L36,   R30, R31, R32, R33, R34, R35, R36 ) \
    { \
        L02, L01, L00, \
        L10, L11, L12, \
        L22, L21, L20, \
        L30, L31, L32, \
        L33, L34, L35, L36, \
        L26, L25, L24, L23, \
        L13, L14, L15, L16, \
        L06, L05, L04, L03, \
        R03, R02, R01, R00, \
        R10, R11, R12, R13, \
        R23, R22, R21, R20, \
        R30, R31, R32, R33, \
        R34, R35, R36, \
        R26, R25, R24, \
        R14, R15, R16, \
        R06, R05, R04 }

#    define RGBLIGHT_LED_MAP LED_LAYOUT( \
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, \
    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, \
    28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, \
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55 )
// clang-format on
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT 56
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_KEYRELEASES
#    define SPLIT_TRANSPORT_MIRROR
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT \
        { RGBLED_NUM_LEFT, RGBLED_NUM_RIGHT }
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#    ifndef RGB_DISABLE_WHEN_USB_SUSPENDED
#        define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    endif
#endif

/* Split communication setting */
#define SOFT_SERIAL_PIN B6 // USART TX pin
#define SELECT_SOFT_SERIAL_SPEED \
    1                              // or 0, 2, 3, 4, 5
                                   //  0: about 460800 baud
                                   //  1: about 230400 baud (default)
                                   //  2: about 115200 baud
                                   //  3: about 57600 baud
                                   //  4: about 38400 baud
                                   //  5: about 19200 baud
#define SERIAL_USART_DRIVER SD1    // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 0 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 10

#define SPLIT_USB_DETECT
#define SPLIT_HAND_PIN B12

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

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

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

/* i2c settings */
#define I2C_DRIVER I2CD2
#define I2C1_SCL_BANK GPIOB
#define I2C1_SCL 10
#define I2C1_SDA_BANK GPIOB
#define I2C1_SDA 11
#define I2C1_TIMINGR_PRESC 2U
#define I2C1_TIMINGR_SCLDEL 1U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 9U
#define I2C1_TIMINGR_SCLL 26U
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define EEPROM_I2C_24LC64
