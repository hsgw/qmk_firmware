/*
Copyright 2021 Takuya Urakawa

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

/* USB Device descriptor parameter
 *
 * VID/PID pair is provided from Microchip
 * Don't use this except for pro micro(ATMEGA32u4)
 */
#define VENDOR_ID 0x04D8
#define PRODUCT_ID 0xE8DF
#define DEVICE_VER 0x0001
#define MANUFACTURER Microchip
#define PRODUCT patchwork

/* key matrix size
 * Dummy keys for encoder (+2 col)
 */
#define MATRIX_ROWS 1
#define MATRIX_COLS 15

/* Key pin assignments
 * D0 is dummy for encoder (unused)
 */
#define DIRECT_PINS                                                    \
    {                                                                  \
        { F5, F4, D3, D2, F6, F7, B1, E6, B3, B2, B6, B5, B4, D0, D0 } \
    }

#define UNUSED_PINS

/* Rotary encoder pin assignments */
#define ENCODERS_PAD_A \
    { C6 }
#define ENCODERS_PAD_B \
    { D7 }

/* Rotary encoder tap delay */
#define ENCODER_TAP_DELAY 1

/* Rotary encoder keycode position in keymap */
#define ENC_KEYMAP_ROW 0
#define ENC_KEYMAP_COL_CW 14
#define ENC_KEYMAP_COL_CCW 13

/* RGB Matrix settings */
#define RGB_DI_PIN D4
// The number of LEDs connected
#define DRIVER_LED_TOTAL 13

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_STARTUP_VAL 127
#define RGB_DISABLE_WHEN_USB_SUSPENDED true

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

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
