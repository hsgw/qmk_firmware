#include "util.h"
#include "stdio.h"

uint8_t brightness = 0;

rgbled_color_t get_current_color(void) {
    return (rgbled_color_t){ rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val()};
}

void set_brightness(uint8_t val) {
    rgbled_color_t current = get_current_color();
    rgblight_sethsv_noeeprom(current.hue, current.sat, val);
    rgblight_set();
}

void step_brightness(void) {
    if(brightness == 0) brightness = BRIGHTNESS_STEP;
    else brightness--;
    set_brightness(RGBLIGHT_LIMIT_VAL/BRIGHTNESS_STEP*brightness);
}

void dump_current_color(void) {
    char str[15] = {'\0'};
    rgbled_color_t current = get_current_color();
    sprintf(str, "%d/%d/%d ", current.hue, current.sat, current.val);
    send_string(str);
}
