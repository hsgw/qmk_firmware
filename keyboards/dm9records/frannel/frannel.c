#include "frannel.h"

static const pin_t led_pins[]   = LED_PINS;
bool               led_states[] = {false, false};

bool     enable_haptic_led = false;
uint16_t haptic_led_timer  = 0;

#ifndef FRANNEL_DISABLE_DYNAMIC_LED_MODE
typedef union {
    uint32_t raw;
    struct {
        uint8_t led_modes[2];
        int8_t  haptic_led_no;
    };
} user_config_t;

user_config_t user_config;
#endif

void frannel_led_set(uint8_t no, bool state) {
    led_states[no] = state;
    writePin(led_pins[no], state);
}

void frannel_led_toggle_temp(uint8_t no) {
    writePin(led_pins[no], !led_states[no]);
}

void frannel_led_restore(void) {
    writePin(led_pins[0], led_states[0]);
    writePin(led_pins[1], led_states[1]);
}

bool frannel_led_get_state(uint8_t no) {
    return led_states[no];
}

void frannel_haptic_led_enable(bool flag) {
    enable_haptic_led = flag;
    if (flag == false) {
        frannel_led_restore();
    }
}

void frannel_solenoid_enable(bool flag) {
    if (flag) {
        haptic_enable();
    } else {
        haptic_disable();
    }

#ifndef FRANNEL_DISABLE_DYNAMIC_LED_MODE
    for (uint8_t i = 0; i < 2; i++) {
        if (user_config.led_modes[i] == FR_LED_SOLENOID) {
            frannel_led_set(i, haptic_get_enable());
        }
    }
#endif
}

#ifndef FRANNEL_DISABLE_DYNAMIC_LED_MODE
void update_led_status(void) {
    for (uint8_t i = 0; i < 2; i++) {
        switch (user_config.led_modes[i]) {
            case FR_LED_NO:
                frannel_led_set(i, 0);
                break;
            case FR_LED_CAPSLOCK:
                frannel_led_set(i, host_keyboard_led_state().caps_lock);
                break;
            case FR_LED_NUMLOCK:
                frannel_led_set(i, host_keyboard_led_state().num_lock);
                break;
            case FR_LED_SOLENOID:
                frannel_led_set(i, haptic_get_enable());
                break;
            default:
                // FR_LED_LAYER
                frannel_led_set(i, layer_state_is(user_config.led_modes[i] - FR_LED_LAYER));
                break;
        }
    }
}

void frannel_led_mode_set_noeeprom(uint8_t no, uint8_t mode) {
    user_config.led_modes[no] = mode;
    update_led_status();
}

void frannel_led_mode_set(uint8_t no, uint8_t mode) {
    frannel_led_mode_set_noeeprom(no, mode);
    eeconfig_update_user(user_config.raw);
}

void frannel_haptic_led_set_noeeprom(int8_t no) {
    frannel_led_restore();
    user_config.haptic_led_no = no;
}

void frannel_haptic_led_set(int8_t no) {
    frannel_haptic_led_set_noeeprom(no);
    eeconfig_update_user(user_config.raw);
}

void eeconfig_init_user(void) { // EEPROM is getting reset!
    user_config.raw           = 0;
    user_config.led_modes[0]  = DEFAULT_LED0_MODE;
    user_config.led_modes[1]  = DEFAULT_LED1_MODE;
    user_config.haptic_led_no = DEFAULT_HAPTIC_LED_NO;

    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_kb(void) {
    user_config.raw = eeconfig_read_user();
    update_led_status();
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // for haptic leds
    if (enable_haptic_led && user_config.haptic_led_no != -1 && record->event.pressed) {
        haptic_led_timer = timer_read();
        frannel_led_toggle_temp(user_config.haptic_led_no);
    }

    if (FR_LED0_NO <= keycode && keycode <= FR_LED1_L5 && record->event.pressed) {
        uint8_t led_no = keycode < FR_LED1_NO ? 0 : 1;
        uint8_t mode   = keycode - (led_no == 0 ? FR_LED0_NO : FR_LED1_NO);
        frannel_led_mode_set(led_no, mode);
        return false;
    }

    if ((keycode == FR_HAPLED_NO || keycode == FR_HAPLED_0 || keycode == FR_HAPLED_1) && record->event.pressed) {
        frannel_haptic_led_set((int8_t)keycode - FR_HAPLED_0);
    }

    return process_record_user(keycode, record);
}

void housekeeping_task_kb(void) {
    if (enable_haptic_led && TIMER_DIFF_16(timer_read(), haptic_led_timer) > TYPE_LED_DWELL) {
        frannel_led_restore();
    }
    housekeeping_task_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        for (uint8_t i = 0; i < 2; i++) {
            if (user_config.led_modes[i] == FR_LED_CAPSLOCK)
                frannel_led_set(i, led_state.caps_lock);
            else if (user_config.led_modes[i] == FR_LED_NUMLOCK)
                frannel_led_set(i, led_state.num_lock);
        }
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(layer_state);
    for (uint8_t i = 0; i < 2; i++) {
        if (user_config.led_modes[i] >= FR_LED_LAYER) {
            uint8_t layer = user_config.led_modes[i] - FR_LED_LAYER;
            frannel_led_set(i, layer == current_layer);
        }
    }
    return layer_state_set_user(state);
}

#endif

void keyboard_pre_init_kb(void) {
    setPinOutput(led_pins[0]);
    setPinOutput(led_pins[1]);

    writePin(led_pins[0], 1);
    writePin(led_pins[1], 1);
    wait_ms(500);

    keyboard_pre_init_user();
}
