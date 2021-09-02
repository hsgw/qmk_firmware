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

#include "midi.h"
extern MidiDevice midi_device;
extern midi_config_t midi_config;

// Initial velocity value (avoid using 127 since it is used as a special number in some sound sources.)
#define MIDI_INITIAL_VELOCITY 117

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
extern rgblight_config_t rgblight_config;
#endif

#define HSV_GRAY 0, 0, 127

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _CHROMA4TH = 0,
    _INKEY4TH,
    _CHROMA3RD,
    _INKEY3RD,
    _SEQUENT,
    _PIANO,
    _DRUM,
    _BLANK,
    _CONFIG
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CH1 = SAFE_RANGE,
    CH2,
    CH3,

    CH1_L1,
    CH1_L2,
    CH1_L3,
    CH1_L4,
    CH1_L5,
    CH1_L6,
    CH1_L7,
    CH1_L8,

    CH2_L1,
    CH2_L2,
    CH2_L3,
    CH2_L4,
    CH2_L5,
    CH2_L6,
    CH2_L7,
    CH2_L8,

    CH3_L1,
    CH3_L2,
    CH3_L3,
    CH3_L4,
    CH3_L5,
    CH3_L6,
    CH3_L7,
    CH3_L8
};

static uint8_t ch1_layer = _CHROMA4TH;
static uint8_t ch2_layer = _PIANO;
static uint8_t ch3_layer = _DRUM;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CHROMA4TH] = LAYOUT(
        CH1,     CH2,     CH3,     TO(_CONFIG),      _______, _______, RGB_TOG,

        MI_B_4,  MI_C_5,  MI_Cs_5, MI_D_5,  MI_Ds_5, MI_E_5,  MI_F_5,  MI_Fs_5,
        MI_Fs_4, MI_G_4,  MI_Gs_4, MI_A_4,  MI_As_4, MI_B_4,  MI_C_5,  MI_Cs_5,
        MI_Cs_4, MI_D_4,  MI_Ds_4, MI_E_4,  MI_F_4,  MI_Fs_4, MI_G_4,  MI_Gs_4,
        MI_Gs_3, MI_A_3,  MI_As_3, MI_B_3,  MI_C_4,  MI_Cs_4, MI_D_4,  MI_Ds_4,
        MI_Ds_3, MI_E_3,  MI_F_3,  MI_Fs_3, MI_G_3,  MI_Gs_3, MI_A_3,  MI_As_3,
        MI_As_2, MI_B_2,  MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3, MI_E_3,  MI_F_3,
        MI_F_2,  MI_Fs_2, MI_G_2,  MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2,  MI_C_3,
        MI_C_2,  MI_Cs_2, MI_D_2,  MI_Ds_2, MI_E_2,  MI_F_2,  MI_Fs_2, MI_G_2
    ),
    [_INKEY4TH] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        MI_C_5,  MI_D_5,  MI_E_5,  MI_F_5,  MI_G_5,  MI_A_5,  MI_B_5,  XXXXXXX,
        MI_G_4,  MI_A_4,  MI_B_4,  MI_C_5,  MI_D_5,  MI_E_5,  MI_F_5,  MI_G_5,
        MI_D_4,  MI_E_4,  MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,  MI_C_5,  MI_D_5,
        MI_A_3,  MI_B_3,  MI_C_4,  MI_D_4,  MI_E_4,  MI_F_4,  MI_G_4,  MI_A_4,
        MI_E_3,  MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3,  MI_C_4,  MI_D_4,  MI_E_4,
        MI_B_2,  MI_C_3,  MI_D_3,  MI_E_3,  MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3,
        MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_C_3,  MI_D_3,  MI_E_3,  MI_F_3,
        MI_C_2,  MI_D_2,  MI_E_2,  MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_C_3
    ),
    [_CHROMA3RD] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        MI_E_4,  MI_F_4,  MI_Fs_4, MI_G_4,  MI_Gs_4, MI_A_4,  MI_As_4, MI_B_4,
        MI_C_4,  MI_Cs_4, MI_D_4,  MI_Ds_4, MI_E_4,  MI_F_4,  MI_Fs_4, MI_G_4,
        MI_Gs_3, MI_A_3,  MI_As_3, MI_B_3,  MI_C_4,  MI_Cs_4, MI_D_4,  MI_Ds_4,
        MI_E_3,  MI_F_3,  MI_Fs_3, MI_G_3,  MI_Gs_3, MI_A_3,  MI_As_3, MI_B_3,
        MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3, MI_E_3,  MI_F_3,  MI_Fs_3, MI_G_3,
        MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2,  MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3,
        MI_E_2,  MI_F_2,  MI_Fs_2, MI_G_2,  MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2,
        MI_C_2,  MI_Cs_2, MI_D_2,  MI_Ds_2, MI_E_2,  MI_F_2,  MI_Fs_2, MI_G_2
    ),
    [_INKEY3RD] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        MI_E_4,  MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,  MI_C_5,  MI_D_5,  MI_E_5,
        MI_C_4,  MI_D_4,  MI_E_4,  MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,  MI_C_5,
        MI_A_3,  MI_B_3,  MI_C_4,  MI_D_4,  MI_E_4,  MI_F_4,  MI_G_4,  MI_A_4,
        MI_E_3,  MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3,  MI_C_4,  MI_D_4,  MI_E_4,
        MI_C_3,  MI_D_3,  MI_E_3,  MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3,  MI_C_4,
        MI_A_2,  MI_B_2,  MI_C_3,  MI_D_3,  MI_E_3,  MI_F_3,  MI_G_3,  MI_A_3,
        MI_E_2,  MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_C_3,  MI_D_3,  MI_E_3,
        MI_C_2,  MI_D_2,  MI_E_2,  MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_C_3
    ),
    [_SEQUENT] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        // MI_Gs_6, MI_A_6,  MI_As_6, MI_B_6,  MI_C_7,  MI_Cs_7, MI_D_7,  MI_Ds_7,
        // MI_C_6,  MI_Cs_6, MI_D_6,  MI_Ds_6, MI_E_6,  MI_F_6,  MI_Fs_6, MI_G_6,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        MI_E_5,  MI_F_5,  MI_Fs_5, MI_G_5,  MI_Gs_5, MI_A_5,  MI_As_5, MI_B_5,
        MI_Gs_4, MI_A_4,  MI_As_4, MI_B_4,  MI_C_5,  MI_Cs_5, MI_D_5,  MI_Ds_5,
        MI_C_4,  MI_Cs_4, MI_D_4,  MI_Ds_4, MI_E_4,  MI_F_4,  MI_Fs_4, MI_G_4,
        MI_E_3,  MI_F_3,  MI_Fs_3, MI_G_3,  MI_Gs_3, MI_A_3,  MI_As_3, MI_B_3,
        MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2,  MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3,
        MI_C_2,  MI_Cs_2, MI_D_2,  MI_Ds_2, MI_E_2,  MI_F_2,  MI_Fs_2, MI_G_2
    ),
    [_PIANO] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        XXXXXXX, MI_Cs_4, MI_Ds_4, XXXXXXX, MI_Fs_4, MI_Gs_4, MI_As_4, XXXXXXX,
        MI_C_4,  MI_D_4,  MI_E_4,  MI_F_4,  MI_G_4,  MI_A_4,  MI_B_4,  MI_C_5,
        XXXXXXX, MI_Cs_3, MI_Ds_3, XXXXXXX, MI_Fs_3, MI_Gs_3, MI_As_3, XXXXXXX,
        MI_C_3,  MI_D_3,  MI_E_3,  MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3,  MI_C_4,
        XXXXXXX, MI_Cs_2, MI_Ds_2, XXXXXXX, MI_Fs_2, MI_Gs_2, MI_As_2, XXXXXXX,
        MI_C_2,  MI_D_2,  MI_E_2,  MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_C_3,
        XXXXXXX, MI_Cs_1, MI_Ds_1, XXXXXXX, MI_Fs_1, MI_Gs_1, MI_As_1, XXXXXXX,
        MI_C_1,  MI_D_1,  MI_E_1,  MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1,  MI_C_2
    ),
    [_DRUM] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        MI_E_3,  MI_F_3,  MI_Fs_3, MI_G_3,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3, MI_Gs_5, MI_A_5,  MI_As_5, MI_B_5,
        MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2,  MI_E_5,  MI_F_5,  MI_Fs_5, MI_G_5,
        MI_E_2,  MI_F_2,  MI_Fs_2, MI_G_2,  MI_C_5,  MI_Cs_5, MI_D_5,  MI_Ds_5,
        MI_C_2,  MI_Cs_2, MI_D_2,  MI_Ds_2, MI_Gs_4, MI_A_4,  MI_As_4, MI_B_4,
        MI_Gs_1, MI_A_1,  MI_As_1, MI_B_1,  MI_E_4,  MI_F_4,  MI_Fs_4, MI_G_4,
        MI_E_1,  MI_F_1,  MI_Fs_1, MI_G_1,  MI_C_4,  MI_Cs_4, MI_D_4,  MI_Ds_4,
        MI_C_1,  MI_Cs_1, MI_D_1,  MI_Ds_1, MI_Gs_3, MI_A_3,  MI_As_3, MI_B_3
    ),
    [_BLANK] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_CONFIG] = LAYOUT(
        _______, _______, _______, _______,          _______, _______, _______,

        CH1_L1,  CH2_L1,  CH3_L1,  XXXXXXX, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
        CH1_L2,  CH2_L2,  CH3_L2,  XXXXXXX, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD,
        CH1_L3,  CH2_L3,  CH3_L3,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        CH1_L4,  CH2_L4,  CH3_L4,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        CH1_L5,  CH2_L5,  CH3_L5,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        CH1_L6,  CH2_L6,  CH3_L6,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        CH1_L7,  CH2_L7,  CH3_L7,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        CH1_L8,  CH2_L8,  CH3_L8,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case CH1:
                layer_move(ch1_layer);
                midi_config.channel = 0;
                return false;
            case CH2:
                layer_move(ch2_layer);
                midi_config.channel = 1;
                return false;
            case CH3:
                layer_move(ch3_layer);
                midi_config.channel = 2;
                return false;

            case CH1_L1:
                ch1_layer = _CHROMA4TH;
                return false;
            case CH1_L2:
                ch1_layer = _INKEY4TH;
                return false;
            case CH1_L3:
                ch1_layer = _CHROMA3RD;
                return false;
            case CH1_L4:
                ch1_layer = _INKEY3RD;
                return false;
            case CH1_L5:
                ch1_layer = _SEQUENT;
                return false;
            case CH1_L6:
                ch1_layer = _PIANO;
                return false;
            case CH1_L7:
                ch1_layer = _DRUM;
                return false;
            case CH1_L8:
                ch1_layer = _BLANK;
                return false;

            case CH2_L1:
                ch2_layer = _CHROMA4TH;
                return false;
            case CH2_L2:
                ch2_layer = _INKEY4TH;
                return false;
            case CH2_L3:
                ch2_layer = _CHROMA3RD;
                return false;
            case CH2_L4:
                ch2_layer = _INKEY3RD;
                return false;
            case CH2_L5:
                ch2_layer = _SEQUENT;
                return false;
            case CH2_L6:
                ch2_layer = _PIANO;
                return false;
            case CH2_L7:
                ch2_layer = _DRUM;
                return false;
            case CH2_L8:
                ch2_layer = _BLANK;
                return false;

            case CH3_L1:
                ch3_layer = _CHROMA4TH;
                return false;
            case CH3_L2:
                ch3_layer = _INKEY4TH;
                return false;
            case CH3_L3:
                ch3_layer = _CHROMA3RD;
                return false;
            case CH3_L4:
                ch3_layer = _INKEY3RD;
                return false;
            case CH3_L5:
                ch3_layer = _SEQUENT;
                return false;
            case CH3_L6:
                ch3_layer = _PIANO;
                return false;
            case CH3_L7:
                ch3_layer = _DRUM;
                return false;
            case CH3_L8:
                ch3_layer = _BLANK;
                return false;
        }
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            midi_config.octave--;
        } else {
            midi_config.octave++;
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            if (midi_config.velocity == 127) {
                midi_config.velocity -= 10;
            } else if (midi_config.velocity > 12) {
                midi_config.velocity -= 13;
            } else {
                midi_config.velocity = 0;
            }
        } else {
            if (midi_config.velocity < 115) {
                midi_config.velocity += 13;
            } else {
                midi_config.velocity = 127;
            }
        }
    } else if (index == 2) { /* Third encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return true;
}

const rgblight_segment_t PROGMEM rgb_chroma4th_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    /* row 1 0-7 */
    {0, 1, HSV_GRAY},
    {1, 1, HSV_RED},
    {3, 1, HSV_GRAY},
    {5, 2, HSV_GRAY},

    /* row 2 8-15 */
    {9, 1, HSV_GRAY},
    {10, 1, HSV_GRAY},
    {13, 1, HSV_GRAY},
    {14, 1, HSV_RED},

    /* row 3 16-23 */
    {17, 1, HSV_GRAY},
    {19, 2, HSV_GRAY},
    {22, 1, HSV_GRAY},

    /* row 4 24-31 */
    {25, 1, HSV_GRAY},
    {27, 1, HSV_GRAY},
    {28, 1, HSV_RED},
    {30, 1, HSV_GRAY},

    /* row 5 32-39 */
    {33, 2, HSV_GRAY},
    {36, 1, HSV_GRAY},
    {38, 1, HSV_GRAY},

    /* row 6 40-47 */
    {41, 1, HSV_GRAY},
    {42, 1, HSV_RED},
    {44, 1, HSV_GRAY},
    {46, 2, HSV_GRAY},

    /* row 7 48-55 */
    {48, 1, HSV_GRAY},
    {50, 1, HSV_GRAY},
    {52, 1, HSV_GRAY},
    {54, 1, HSV_GRAY},
    {55, 1, HSV_RED},

    /* row 8 56-63 */
    {56, 1, HSV_RED},
    {58, 1, HSV_GRAY},
    {60, 2, HSV_GRAY},
    {63, 1, HSV_GRAY}
);

const rgblight_segment_t PROGMEM rgb_inkey4th_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    /* row 1 0-7 */
    {0, 1, HSV_RED},
    {1, 6, HSV_GRAY},
    // {7, 1, HSV_RED},

    /* row 2 8-15 */
    {8, 3, HSV_GRAY},
    {11, 1, HSV_RED},
    {12, 4, HSV_GRAY},

    /* row 3 16-23 */
    {16, 6, HSV_GRAY},
    {22, 1, HSV_RED},
    {23, 1, HSV_GRAY},

    /* row 4 24-31 */
    {24, 2, HSV_GRAY},
    {26, 1, HSV_RED},
    {27, 5, HSV_GRAY},

    /* row 5 32-39 */
    {32, 5, HSV_GRAY},
    {37, 1, HSV_RED},
    {38, 2, HSV_GRAY},

    /* row 6 40-47 */
    {40, 1, HSV_GRAY},
    {41, 1, HSV_RED},
    {42, 6, HSV_GRAY},

    /* row 7 48-55 */
    {48, 4, HSV_GRAY},
    {52, 1, HSV_RED},
    {53, 3, HSV_GRAY},

    /* row 8 56-63 */
    {56, 1, HSV_RED},
    {57, 6, HSV_GRAY},
    {63, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM rgb_chroma3rd_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    /* row 1 0-7 */
    {0, 2, HSV_GRAY},
    {3, 1, HSV_GRAY},
    {5, 1, HSV_GRAY},
    {7, 1, HSV_GRAY},

    /* row 2 8-15 */
    {8, 1, HSV_RED},
    {10, 1, HSV_GRAY},
    {12, 2, HSV_GRAY},
    {15, 1, HSV_GRAY},

    /* row 3 16-23 */
    {17, 1, HSV_GRAY},
    {19, 1, HSV_GRAY},
    {20, 1, HSV_RED},
    {22, 1, HSV_GRAY},

    /* row 4 24-31 */
    {24, 2, HSV_GRAY},
    {27, 1, HSV_GRAY},
    {29, 1, HSV_GRAY},
    {31, 1, HSV_GRAY},

    /* row 5 32-39 */
    {32, 1, HSV_RED},
    {34, 1, HSV_GRAY},
    {36, 2, HSV_GRAY},
    {39, 1, HSV_GRAY},

    /* row 6 40-47 */
    {41, 1, HSV_GRAY},
    {43, 1, HSV_GRAY},
    {44, 1, HSV_RED},
    {46, 1, HSV_GRAY},

    /* row 7 48-55 */
    {48, 2, HSV_GRAY},
    {51, 1, HSV_GRAY},
    {53, 1, HSV_GRAY},
    {55, 1, HSV_GRAY},

    /* row 8 56-63 */
    {56, 1, HSV_RED},
    {58, 1, HSV_GRAY},
    {60, 2, HSV_GRAY},
    {63, 1, HSV_GRAY}
);

const rgblight_segment_t PROGMEM rgb_inkey3rd_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    /* row 1 0-7 */
    {0, 5, HSV_GRAY},
    {5, 1, HSV_RED},
    {6, 2, HSV_GRAY},

    /* row 2 8-15 */
    {8, 1, HSV_RED},
    {9, 6, HSV_GRAY},
    {15, 1, HSV_RED},

    /* row 3 16-23 */
    {16, 2, HSV_GRAY},
    {18, 1, HSV_RED},
    {19, 5, HSV_GRAY},

    /* row 4 24-31 */
    {24, 5, HSV_GRAY},
    {29, 1, HSV_RED},
    {30, 2, HSV_GRAY},

    /* row 5 32-39 */
    {32, 1, HSV_RED},
    {33, 6, HSV_GRAY},
    {39, 1, HSV_RED},

    /* row 6 40-47 */
    {40, 2, HSV_GRAY},
    {42, 1, HSV_RED},
    {43, 5, HSV_GRAY},

    /* row 7 48-55 */
    {48, 5, HSV_GRAY},
    {53, 1, HSV_RED},
    {54, 2, HSV_GRAY},

    /* row 8 56-63 */
    {56, 1, HSV_RED},
    {57, 6, HSV_GRAY},
    {63, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM rgb_sequent_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // /* row 1 0-7 */
    // {1, 1, HSV_GRAY},
    // {3, 1, HSV_GRAY},
    // {4, 1, HSV_RED},
    // {6, 1, HSV_GRAY},

    // /* row 2 8-15 */
    // {8, 1, HSV_RED},
    // {10, 1, HSV_GRAY},
    // {12, 2, HSV_GRAY},
    // {15, 1, HSV_GRAY},

    /* row 3 16-23 */
    {16, 2, HSV_GRAY},
    {19, 1, HSV_GRAY},
    {21, 1, HSV_GRAY},
    {23, 1, HSV_GRAY},

    /* row 4 24-31 */
    {25, 1, HSV_GRAY},
    {27, 1, HSV_GRAY},
    {28, 1, HSV_RED},
    {30, 1, HSV_GRAY},

    /* row 5 32-39 */
    {32, 1, HSV_RED},
    {34, 1, HSV_GRAY},
    {36, 2, HSV_GRAY},
    {39, 1, HSV_GRAY},

    /* row 6 40-47 */
    {40, 2, HSV_GRAY},
    {43, 1, HSV_GRAY},
    {45, 1, HSV_GRAY},
    {47, 1, HSV_GRAY},

    /* row 7 48-55 */
    {49, 1, HSV_GRAY},
    {51, 1, HSV_GRAY},
    {52, 1, HSV_RED},
    {54, 1, HSV_GRAY},

    /* row 8 56-63 */
    {56, 1, HSV_RED},
    {58, 1, HSV_GRAY},
    {60, 2, HSV_GRAY},
    {63, 1, HSV_GRAY}
);

const rgblight_segment_t PROGMEM rgb_piano_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    /* row 1 0-7 */
    {1, 2, HSV_GRAY},
    {4, 3, HSV_GRAY},
    /* row 2 8-15 */
    {8, 1, HSV_RED},
    {9, 6, HSV_GRAY},
    {15, 1, HSV_RED},

    /* row 3 16-23 */
    {17, 2, HSV_GRAY},
    {20, 3, HSV_GRAY},
    /* row 4 24-31 */
    {24, 1, HSV_RED},
    {25, 6, HSV_GRAY},
    {31, 1, HSV_RED},

    /* row 5 32-39 */
    {33, 2, HSV_GRAY},
    {36, 3, HSV_GRAY},
    /* row 6 40-47 */
    {40, 1, HSV_RED},
    {41, 6, HSV_GRAY},
    {47, 1, HSV_RED},

    /* row 7 48-55 */
    {49, 2, HSV_GRAY},
    {52, 3, HSV_GRAY},
    /* row 8 56-63 */
    {56, 1, HSV_RED},
    {57, 6, HSV_GRAY},
    {63, 1, HSV_RED}
);


const rgblight_segment_t PROGMEM rgb_drum_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    /* upper left */
    {0, 4, HSV_GRAY},
    {8, 4, HSV_GRAY},
    {16, 4, HSV_GRAY},
    {24, 4, HSV_GRAY},

    /* upper right */
    {4, 4, HSV_RED},
    {12, 4, HSV_RED},
    {20, 4, HSV_RED},
    {28, 4, HSV_RED},

    /* lower left */
    {32, 4, HSV_RED},
    {40, 4, HSV_RED},
    {48, 4, HSV_RED},
    {56, 4, HSV_RED},

    /* lower right */
    {36, 4, HSV_GRAY},
    {44, 4, HSV_GRAY},
    {52, 4, HSV_GRAY},
    {60, 4, HSV_GRAY}
);

// const rgblight_segment_t PROGMEM rgb_blank_layer[] = RGBLIGHT_LAYER_SEGMENTS(
// );

const rgblight_segment_t PROGMEM rgb_config_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    /* layer control */
    {0, 1, HSV_PURPLE},  {1, 1, HSV_MAGENTA},  {2, 1, HSV_PINK},
    {8, 1, HSV_PURPLE},  {9, 1, HSV_MAGENTA},  {10, 1, HSV_PINK},
    {16, 1, HSV_PURPLE}, {17, 1, HSV_MAGENTA}, {18, 1, HSV_PINK},
    {24, 1, HSV_PURPLE}, {25, 1, HSV_MAGENTA}, {26, 1, HSV_PINK},
    {32, 1, HSV_PURPLE}, {33, 1, HSV_MAGENTA}, {34, 1, HSV_PINK},
    {40, 1, HSV_PURPLE}, {41, 1, HSV_MAGENTA}, {42, 1, HSV_PINK},
    {48, 1, HSV_PURPLE}, {49, 1, HSV_MAGENTA}, {50, 1, HSV_PINK},
    {56, 1, HSV_PURPLE}, {57, 1, HSV_MAGENTA}, {58, 1, HSV_PINK},

    /* led control */
    {4, 1, HSV_WHITE},  {5, 1, HSV_RED},  {6, 1, HSV_ORANGE},  {7, 1, HSV_YELLOW},
    {12, 1, HSV_WHITE}, {13, 1, HSV_RED}, {14, 1, HSV_ORANGE}, {15, 1, HSV_YELLOW}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_chroma4th_layer,
    rgb_inkey4th_layer,
    rgb_chroma3rd_layer,
    rgb_inkey3rd_layer,
    rgb_sequent_layer,
    rgb_piano_layer,
    rgb_drum_layer,
    // rgb_blank_layer,
    rgb_config_layer
);

void keyboard_post_init_user(void) {
    //  Set otave to MI_OCT_0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;
    midi_config.velocity = MIDI_INITIAL_VELOCITY;

#ifdef RGBLIGHT_ENABLE
    rgblight_layers = rgb_layers;
    // Reset LED off
    rgblight_sethsv(0, 255, 0);
#endif
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CHROMA4TH));
    rgblight_set_layer_state(1, layer_state_cmp(state, _INKEY4TH));
    rgblight_set_layer_state(2, layer_state_cmp(state, _CHROMA3RD));
    rgblight_set_layer_state(3, layer_state_cmp(state, _INKEY3RD));
    rgblight_set_layer_state(4, layer_state_cmp(state, _SEQUENT));
    rgblight_set_layer_state(5, layer_state_cmp(state, _PIANO));
    rgblight_set_layer_state(6, layer_state_cmp(state, _DRUM));
    // rgblight_set_layer_state(7, layer_state_cmp(state, _BLANK));
    rgblight_set_layer_state(7, layer_state_cmp(state, _CONFIG));
    return state;
}
