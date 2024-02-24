#include "frannel.h"

static const pin_t led_pins[]   = LED_PINS;
bool               led_states[] = {false, false};

bool     enable_haptic_led = false;
uint16_t haptic_led_timer  = 0;

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

void frannel_enable_haptic_led(bool flag) {
    enable_haptic_led = flag;
    if (flag == false) {
        frannel_led_restore();
    }
}

void keyboard_pre_init_kb(void) {
    for (uint8_t i = 0; i < 2; i++) {
        setPinOutput(led_pins[i]);
    }
    keyboard_pre_init_user();
}
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (enable_haptic_led && record->event.pressed) {
        haptic_led_timer = timer_read();
        frannel_led_toggle_temp(1);
    }
    return process_record_user(keycode, record);
};
void housekeeping_task_kb(void) {
    if (enable_haptic_led && TIMER_DIFF_16(timer_read(), haptic_led_timer) > TYPE_LED_DWELL) {
        frannel_led_restore();
    }
    housekeeping_task_user();
}
