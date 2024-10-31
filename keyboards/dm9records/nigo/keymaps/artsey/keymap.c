// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _ART_BASE,
    _ART_NUM,
    _ART_CUS,
    _ART_PUNC,
    _ART_MOU,
    _ART_NAV,
    _ART_SYM,
};

#include "aliases.c"
#include "combos.c"

// copied from https://beta.docs.qmk.fm/faqs/faq_debug#which-matrix-position-is-this-keypress
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_ART_BASE] = LAYOUT(
BASE_1_1,BASE_1_2,BASE_1_3,BASE_1_4, KC_BSPC,
BASE_2_1,BASE_2_2,BASE_2_3,BASE_2_4, KC_SPC
),

[_ART_NUM] = LAYOUT(
NUM_1_1,NUM_1_2,NUM_1_3,NUM_1_4, KC_BSPC,
NUM_2_1,NUM_2_2,NUM_2_3,NUM_2_4, KC_SPC
),


[_ART_PUNC] = LAYOUT(
PUNC_1_1,PUNC_1_2,PUNC_1_3,PUNC_1_4, KC_BSPC,
PUNC_2_1,PUNC_2_2,PUNC_2_3,PUNC_2_4, KC_SPC
),

[_ART_CUS] = LAYOUT(
CUS_1_1,CUS_1_2,CUS_1_3,CUS_1_4, KC_BSPC,
CUS_2_1,CUS_2_2,CUS_2_3,CUS_2_4, KC_SPC
),

[_ART_SYM] = LAYOUT(
SYM_1_1,SYM_1_2,SYM_1_3,SYM_1_4, KC_BSPC,
SYM_2_1,SYM_2_2,SYM_2_3,SYM_2_4, KC_SPC
),

[_ART_MOU] = LAYOUT(
MOU_1_1,MOU_1_2,MOU_1_3,MOU_1_4, KC_BSPC,
MOU_2_1,MOU_2_2,MOU_2_3,MOU_2_4, KC_SPC
),

[_ART_NAV] = LAYOUT(
NAV_1_1,NAV_1_2,NAV_1_3,NAV_1_4, KC_BSPC,
NAV_2_1,NAV_2_2,NAV_2_3,NAV_2_4, KC_SPC
),
};

// clang-format on
