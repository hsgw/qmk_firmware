/* Copyright 2021 yynmt
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    TEST
};

enum custom_keycodes {
    MY_CUSTOM_MACRO = SAFE_RANGE,
    TS1,
    TS2,
    TS3,
    TS4,

    RE1,
    RE2,
    RE3,

    MX11,
    MX12,
    MX13,
    MX14,
    MX15,
    MX16,
    MX17,
    MX18,

    MX21,
    MX22,
    MX23,
    MX24,
    MX25,
    MX26,
    MX27,
    MX28,

    MX31,
    MX32,
    MX33,
    MX34,
    MX35,
    MX36,
    MX37,
    MX38,

    MX41,
    MX42,
    MX43,
    MX44,
    MX45,
    MX46,
    MX47,
    MX48,

    MX51,
    MX52,
    MX53,
    MX54,
    MX55,
    MX56,
    MX57,
    MX58,

    MX61,
    MX62,
    MX63,
    MX64,
    MX65,
    MX66,
    MX67,
    MX68,

    MX71,
    MX72,
    MX73,
    MX74,
    MX75,
    MX76,
    MX77,
    MX78,

    MX81,
    MX82,
    MX83,
    MX84,
    MX85,
    MX86,
    MX87,
    MX88
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [TEST] = LAYOUT(
        TS1, TS2, TS3, TS4, RE1, RE2, RE3,

        MX11, MX12, MX13, MX14, MX15, MX16, MX17, MX18,
        MX21, MX22, MX23, MX24, MX25, MX26, MX27, MX28,
        MX31, MX32, MX33, MX34, MX35, MX36, MX37, MX38,
        MX41, MX42, MX43, MX44, MX45, MX46, MX47, MX48,
        MX51, MX52, MX53, MX54, MX55, MX56, MX57, MX58,
        MX61, MX62, MX63, MX64, MX65, MX66, MX67, MX68,
        MX71, MX72, MX73, MX74, MX75, MX76, MX77, MX78,
        MX81, MX82, MX83, MX84, MX85, MX86, MX87, MX88
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	  if (record->event.pressed) {
		    switch(keycode) {
            case TS1:
                SEND_STRING("Tactile Switch 1\n");
                return false;
            case TS2:
                SEND_STRING("Tactile Switch 2\n");
                return false;
            case TS3:
                SEND_STRING("Tactile Switch 3\n");
                return false;
            case TS4:
                SEND_STRING("Tactile Switch 4\n");
                return false;

            case RE1:
                SEND_STRING("Rotary Eoncder 1\n");
                return false;
            case RE2:
                SEND_STRING("Rotary Eoncder 2\n");
                return false;
            case RE3:
                SEND_STRING("Rotary Eoncder 3\n");
                return false;

            case MX11:
                SEND_STRING("MX Switch 1-1\n");
                return false;
            case MX12:
                SEND_STRING("MX Switch 1-2\n");
                return false;
            case MX13:
                SEND_STRING("MX Switch 1-3\n");
                return false;
            case MX14:
                SEND_STRING("MX Switch 1-4\n");
                return false;
            case MX15:
                SEND_STRING("MX Switch 1-5\n");
                return false;
            case MX16:
                SEND_STRING("MX Switch 1-6\n");
                return false;
            case MX17:
                SEND_STRING("MX Switch 1-7\n");
                return false;
            case MX18:
                SEND_STRING("MX Switch 1-8\n");
                return false;

            case MX21:
                SEND_STRING("MX Switch 2-1\n");
                return false;
            case MX22:
                SEND_STRING("MX Switch 2-2\n");
                return false;
            case MX23:
                SEND_STRING("MX Switch 2-3\n");
                return false;
            case MX24:
                SEND_STRING("MX Switch 2-4\n");
                return false;
            case MX25:
                SEND_STRING("MX Switch 2-5\n");
                return false;
            case MX26:
                SEND_STRING("MX Switch 2-6\n");
                return false;
            case MX27:
                SEND_STRING("MX Switch 2-7\n");
                return false;
            case MX28:
                SEND_STRING("MX Switch 2-8\n");
                return false;

            case MX31:
                SEND_STRING("MX Switch 3-1\n");
                return false;
            case MX32:
                SEND_STRING("MX Switch 3-2\n");
                return false;
            case MX33:
                SEND_STRING("MX Switch 3-3\n");
                return false;
            case MX34:
                SEND_STRING("MX Switch 3-4\n");
                return false;
            case MX35:
                SEND_STRING("MX Switch 3-5\n");
                return false;
            case MX36:
                SEND_STRING("MX Switch 3-6\n");
                return false;
            case MX37:
                SEND_STRING("MX Switch 3-7\n");
                return false;
            case MX38:
                SEND_STRING("MX Switch 3-8\n");
                return false;

            case MX41:
                SEND_STRING("MX Switch 4-1\n");
                return false;
            case MX42:
                SEND_STRING("MX Switch 4-2\n");
                return false;
            case MX43:
                SEND_STRING("MX Switch 4-3\n");
                return false;
            case MX44:
                SEND_STRING("MX Switch 4-4\n");
                return false;
            case MX45:
                SEND_STRING("MX Switch 4-5\n");
                return false;
            case MX46:
                SEND_STRING("MX Switch 4-6\n");
                return false;
            case MX47:
                SEND_STRING("MX Switch 4-7\n");
                return false;
            case MX48:
                SEND_STRING("MX Switch 4-8\n");
                return false;

            case MX51:
                SEND_STRING("MX Switch 5-1\n");
                return false;
            case MX52:
                SEND_STRING("MX Switch 5-2\n");
                return false;
            case MX53:
                SEND_STRING("MX Switch 5-3\n");
                return false;
            case MX54:
                SEND_STRING("MX Switch 5-4\n");
                return false;
            case MX55:
                SEND_STRING("MX Switch 5-5\n");
                return false;
            case MX56:
                SEND_STRING("MX Switch 5-6\n");
                return false;
            case MX57:
                SEND_STRING("MX Switch 5-7\n");
                return false;
            case MX58:
                SEND_STRING("MX Switch 5-8\n");
                return false;

            case MX61:
                SEND_STRING("MX Switch 6-1\n");
                return false;
            case MX62:
                SEND_STRING("MX Switch 6-2\n");
                return false;
            case MX63:
                SEND_STRING("MX Switch 6-3\n");
                return false;
            case MX64:
                SEND_STRING("MX Switch 6-4\n");
                return false;
            case MX65:
                SEND_STRING("MX Switch 6-5\n");
                return false;
            case MX66:
                SEND_STRING("MX Switch 6-6\n");
                return false;
            case MX67:
                SEND_STRING("MX Switch 6-7\n");
                return false;
            case MX68:
                SEND_STRING("MX Switch 6-8\n");
                return false;

            case MX71:
                SEND_STRING("MX Switch 7-1\n");
                return false;
            case MX72:
                SEND_STRING("MX Switch 7-2\n");
                return false;
            case MX73:
                SEND_STRING("MX Switch 7-3\n");
                return false;
            case MX74:
                SEND_STRING("MX Switch 7-4\n");
                return false;
            case MX75:
                SEND_STRING("MX Switch 7-5\n");
                return false;
            case MX76:
                SEND_STRING("MX Switch 7-6\n");
                return false;
            case MX77:
                SEND_STRING("MX Switch 7-7\n");
                return false;
            case MX78:
                SEND_STRING("MX Switch 7-8\n");
                return false;

            case MX81:
                SEND_STRING("MX Switch 8-1\n");
                return false;
            case MX82:
                SEND_STRING("MX Switch 8-2\n");
                return false;
            case MX83:
                SEND_STRING("MX Switch 8-3\n");
                return false;
            case MX84:
                SEND_STRING("MX Switch 8-4\n");
                return false;
            case MX85:
                SEND_STRING("MX Switch 8-5\n");
                return false;
            case MX86:
                SEND_STRING("MX Switch 8-6\n");
                return false;
            case MX87:
                SEND_STRING("MX Switch 8-7\n");
                return false;
            case MX88:
                SEND_STRING("MX Switch 8-8\n");
                return false;
		    }
	  }
	  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            SEND_STRING("Encoder 1 left\n");
        } else {
            SEND_STRING("Encoder 1 right\n");
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            SEND_STRING("Encoder 2 left\n");
        } else {
            SEND_STRING("Encoder 2 right\n");
        }
    } else if (index == 2) { /* Third encoder */
        if (clockwise) {
            SEND_STRING("Encoder 3 left\n");
        } else {
            SEND_STRING("Encoder 3 right\n");
        }
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
}
