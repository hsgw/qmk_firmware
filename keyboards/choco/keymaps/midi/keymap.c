/* Copyright 2019 Takuya Urakawa, Dm9Recoreds.com
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
#include "midi.h"

extern MidiDevice midi_device;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MIDI_N1 = SAFE_RANGE,
    MIDI_C1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(\
        KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    RESET,  \
        MIDI_N1,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  \
        MIDI_C1,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        MI_C,     MI_D,    MI_E,    MI_F,    MI_G,    MI_A,    MI_B \
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MIDI_N1:
            if (record->event.pressed) {
                midi_send_noteon(&midi_device, 1, 64, 100);
            } else {
                midi_send_noteoff(&midi_device, 1,64, 0);
            }
            break;
        case MIDI_C1:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, 0, 0, 64);
            } else {
                midi_send_cc(&midi_device, 0, 0, 0);
            }
            break;
        default:
            break;
    }
    return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
