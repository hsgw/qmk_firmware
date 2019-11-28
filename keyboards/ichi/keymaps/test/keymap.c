/* Copyright 2019 Takuya Urakawa(dm9records.com 5z6p.com)
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
#include QMK_KEYBOARD_H
#include "../../util.h"

uint8_t current_color = 0;

void set_rgbw(uint8_t num) {
    switch(num) {
        case 0:
            rgblight_sethsv_noeeprom(0,0,0);
            SEND_STRING("OFF");
            break;
        case 1:
            rgblight_sethsv_noeeprom_red();
            SEND_STRING("RED");
            break;
        case 2:
            rgblight_sethsv_noeeprom_green();
            SEND_STRING("GREEN");
            break;
        case 3:
            rgblight_sethsv_noeeprom_blue();
            SEND_STRING("BLUE");
            break;
        case 4:
            rgblight_sethsv_noeeprom_white();
            SEND_STRING("WHITE");
            break;
        default:
            break;
    }
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BIGSW = SAFE_RANGE,
    CONF1,
    CONF2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        BIGSW,    CONF1,    CONF2
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CONF1:
            if (record->event.pressed) {
                if(current_color++ == 4) current_color = 0;
                set_rgbw(current_color);
            }
            break;
        case CONF2:
            if (record->event.pressed) {
                step_brightness();
            }
            break;
        case BIGSW:
            if (record->event.pressed) {
                rgblight_step_noeeprom();
            }
            break;
    }
    return true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
