/* Copyright 2021 Takuya Urakawa
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

#include "patchwork.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {{// Key Matrix to LED Index
                              {3, 2, 1, 0, 4, 5, 6, 7, 12, 11, 10, 9, 8, NO_LED, NO_LED}},
                             {// LED Index to Physical Position
                              {168, 0},
                              {112, 0},
                              {56, 0},
                              {0, 0},
                              {0, 32},
                              {56, 32},
                              {112, 32},
                              {168, 32},
                              {224, 64},
                              {168, 64},
                              {112, 64},
                              {56, 64},
                              {0, 64}},
                             {// LED Index to Flag
                              LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL}};
#endif

// based on attack25_rev32
// https://github.com/monksoffunk/qmk_firmware/blob/feature/attack25_rev3_add/keyboards/25keys/attack25/rev32/rev32.c
bool encoder_update_kb(uint8_t index, bool clockwise) {
    keypos_t encoder_keypos;

    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    if (index == 0) {
        encoder_keypos.row = ENC_KEYMAP_ROW;
        if (clockwise) {
            encoder_keypos.col = ENC_KEYMAP_COL_CW;
        } else {
            encoder_keypos.col = ENC_KEYMAP_COL_CCW;
        }
        action_exec((keyevent_t){.key = encoder_keypos, .pressed = true, .time = (timer_read() | 1)});
        wait_ms(ENCODER_TAP_DELAY);
        action_exec((keyevent_t){.key = encoder_keypos, .pressed = false, .time = (timer_read() | 1)});
    }
    return true;
}
