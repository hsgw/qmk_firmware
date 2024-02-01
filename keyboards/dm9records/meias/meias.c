#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // pull up for handedness pin
    setPinInputHigh(SPLIT_HAND_PIN);

    keyboard_pre_init_user();
}
