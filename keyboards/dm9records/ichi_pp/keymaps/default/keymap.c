// Copyright 2024 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define DESKLIGHT_STEP_MAX 3
#define DESKLIGHT_BRIGHTNESS RGBLIGHT_LIMIT_VAL / DESKLIGHT_STEP_MAX

uint16_t bigsw_timer      = 0;
bool     sw_holding[2]    = {false, false};
uint16_t sw_timer[2]      = {0, 0};
bool     enable_desklight = true;
uint8_t  desklight_step   = DESKLIGHT_STEP_MAX;

void set_desklight_step(uint8_t step) {
    rgblight_sethsv_noeeprom(rgblight_get_hue(), rgblight_get_sat(), step >= 3 ? RGBLIGHT_LIMIT_VAL : step * DESKLIGHT_BRIGHTNESS);
}

void set_desklight_mode(bool enable) {
    enable_desklight = enable;
    if (enable_desklight) {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        desklight_step = DESKLIGHT_STEP_MAX;
        set_desklight_step(desklight_step);
    } else {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
    }
    rgblight_enable_noeeprom();
}

// clang-format off
enum custom_keycodes {
    BIGSW = SAFE_RANGE,
    SW1,
    SW2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        BIGSW, SW1, SW2
    )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BIGSW:
            if (record->event.pressed) {
                bigsw_timer = record->event.time;
                if (sw_holding[0] || sw_holding[1]) {
                    set_desklight_mode(!enable_desklight);
                } else {
                    if (enable_desklight) {
                        if (desklight_step == 0)
                            desklight_step = DESKLIGHT_STEP_MAX;
                        else
                            desklight_step--;

                        set_desklight_step(desklight_step);
                    } else {
                        rgblight_toggle_noeeprom();
                    }
                }
            } else {
                if (TIMER_DIFF_16(record->event.time, bigsw_timer) > BIG_SWITCH_HOLD_TIME) {
                    // save config to eeprom
                    rgblight_mode(rgblight_get_mode());
                    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
                }
            }
            return false;
        case SW1:
            if (record->event.pressed) {
                sw_timer[0]   = record->event.time;
                sw_holding[0] = true;
            } else {
                sw_holding[0] = false;
                if (TIMER_DIFF_16(record->event.time, sw_timer[0]) < TAPPING_TERM) {
                    if (sw_holding[1]) {
                        if (rgblight_get_sat() == 255) {
                            rgblight_sethsv_noeeprom(rgblight_get_hue(), 0, rgblight_get_val());
                        } else {
                            rgblight_increase_sat_noeeprom();
                        }
                    } else {
                        if (!enable_desklight) rgblight_step_noeeprom();
                    }
                }
            }
            return false;
        case SW2:
            if (record->event.pressed) {
                sw_timer[1]   = record->event.time;
                sw_holding[1] = true;
            } else {
                sw_holding[1] = false;
                if (TIMER_DIFF_16(record->event.time, sw_timer[1]) < TAPPING_TERM) {
                    if (sw_holding[0]) {
                        if (rgblight_get_val() >= RGBLIGHT_LIMIT_VAL) {
                            rgblight_sethsv_noeeprom(rgblight_get_hue(), rgblight_get_sat(), 0);
                        } else {
                            rgblight_increase_val_noeeprom();
                        }
                    } else {
                        rgblight_increase_hue_noeeprom();
                    }
                }
            }
            return false;
        default:
            return true;
    }
    return false;
}

void keyboard_post_init_user(void) {
    if (rgblight_get_mode() == RGBLIGHT_MODE_STATIC_LIGHT) {
        enable_desklight = true;
    }
    set_desklight_mode(enable_desklight);
}
