/* Copyright 2019 Takuya Urakawa(hsgw), dm9records.com, 5z6p.com
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

#include "leds.h"
#include "config.h"

static const pin_t leds[LED_NUM] = { LED_PINS };
bool led_states[LED_NUM] = {0};
bool isLedEnabled = true;

void init_leds(void) {
    for(int i=0;i<LED_NUM;i++) {
        setPinOutput(leds[i]);
        writePin(leds[i],0);
    }
}

void set_led(uint8_t no, bool flag) {
    led_states[no] = flag;
    if(isLedEnabled) writePin(leds[no], flag);
}

void set_led_enable(bool flag) {
    isLedEnabled = flag;
    if(isLedEnabled) {
        for(int i=0; i<LED_NUM; i++) writePin(leds[i],led_states[i]);
    } else {
        for(int i=0; i<LED_NUM; i++) writePin(leds[i],0);
    }
}
