#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_P7,   KC_P8,   KC_P9,   KC_PAST,   KC_BSPC,    RESET,
        KC_TAB, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,    KC_EQL,    KC_NLCK,
        KC_LCTL, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,   KC_PSLS,    KC_NLCK,
        KC_LSFT, KC_P0,   KC_PDOT,  KC_COMM,   KC_PENT, KC_SPC,  KC_GRV
    )
};
// clang-format on
