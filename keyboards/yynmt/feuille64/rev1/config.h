/*
Copyright 2021 yynmt

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
#define VENDOR_ID    0x04D8 //Sublicense from Microchip Technology
#define PRODUCT_ID   0xE8D8 //Sublicense from Microchip Technology
#define DEVICE_VER   0x0001
#define MANUFACTURER yynmt
#define PRODUCT      Feuille64

/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 8

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { D0, C7, C6, B6, B5, B4, D7, D6, D4 }
#define MATRIX_COL_PINS { F1, F4, F5, F6, F7, B3, B1, B2}
#define UNUSED_PINS {B0, D5, E6}

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Encoder */
#ifdef ENCODER_ENABLE
#   define ENCODERS_PAD_A { D2, D3, D1 }
#   define ENCODERS_PAD_B { D1, D2, D3 }
#   define ENCODER_RESOLUTION 4
#   define TAP_CODE_DELAY 10
#endif

/* MIDI */
#ifdef MIDI_ENABLE
#   define MIDI_ADVANCED
#endif

#define RGB_DI_PIN F0
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 64
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 120 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
#    define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//#    define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
//#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//#    define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 9

#define LED_LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06, L07, \
  L08, L09, L10, L11, L12, L13, L14, L15, \
  L16, L17, L18, L19, L20, L21, L22, L23, \
  L24, L25, L26, L27, L28, L29, L30, L31, \
  L32, L33, L34, L35, L36, L37, L38, L39, \
  L40, L41, L42, L43, L44, L45, L46, L47, \
  L48, L49, L50, L51, L52, L53, L54, L55, \
  L56, L57, L58, L59, L60, L61, L62, L63  \
) { \
  L00, L01, L02, L03, L04, L05, L06, L07, \
  L15, L14, L13, L12, L11, L10, L09, L08, \
  L16, L17, L18, L19, L20, L21, L22, L23, \
  L31, L30, L29, L28, L27, L26, L25, L24, \
  L32, L33, L34, L35, L36, L37, L38, L39, \
  L47, L46, L45, L44, L43, L42, L41, L40, \
  L48, L49, L50, L51, L52, L53, L54, L55, \
  L63, L62, L61, L60, L59, L58, L57, L56  \
}

#define RGBLIGHT_LED_MAP LED_LAYOUT( \
   0,  1,  2,  3,  4,  5,  6,  7, \
   8,  9, 10, 11, 12, 13, 14, 15, \
  16, 17, 18, 19, 20, 21, 22, 23, \
  24, 25, 26, 27, 28, 29, 30, 31, \
  32, 33, 34, 35, 36, 37, 38, 39, \
  40, 41, 42, 43, 44, 45, 46, 47, \
  48, 49, 50, 51, 52, 53, 54, 55, \
  56, 57, 58, 59, 60, 61, 62, 63  \
)

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
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0
