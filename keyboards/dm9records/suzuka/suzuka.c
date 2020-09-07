/* Copyright 2020 Takuya Urakawa (dm9records.com 5z6p.com)
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

#include "suzuka.h"
#include "split_util.h"

static const uint8_t led_pins[LED_NUM] = LED_PINS;

void keyboard_pre_init_kb(void) {
    // pull up handness pin
    setPinInput(SPLIT_HAND_PIN);
    writePinHigh(SPLIT_HAND_PIN);

    keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    // init leds
    if (isLeftHand) {
        for (uint8_t i = 0; i < LED_NUM; ++i) {
            setPinOutput(led_pins[i]);
        }
    }

    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool ret = led_update_user(led_state);
    if (ret && isLeftHand) {
        writePin(led_pins[0], led_state.num_lock);
        writePin(led_pins[1], led_state.caps_lock);
    }
    return ret;
}

