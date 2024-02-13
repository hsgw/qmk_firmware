#include <quantum.h>

static const pin_t led_pins[]   = LED_PINS;
bool               led_states[] = {false, false};

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

void keyboard_pre_init_kb(void) {
    for (uint8_t i = 0; i < 2; i++) {
        setPinOutput(led_pins[i]);
    }
    keyboard_pre_init_user();
}
