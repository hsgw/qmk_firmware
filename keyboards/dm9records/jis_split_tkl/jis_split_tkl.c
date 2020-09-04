/* Copyright 2020 Takuya Urakawa(Dm9 Records)
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

#include "jis_split_tkl.h"
#include "split_util.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

static const uint8_t led_pins[LED_NUM] = LED_PINS;

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    // init leds
    if (isLeftHand) {
        for (uint8_t i = 0; i < LED_NUM; ++i) {
            setPinOutput(led_pins[i]);
        }
    }

    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    bool ret = led_update_user(led_state);
    if (ret && isLeftHand) {
        writePin(led_pins[0], led_state.num_lock);
        writePin(led_pins[1], led_state.caps_lock);
    }
    return ret;
}

/*
void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}
*/
