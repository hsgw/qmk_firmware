#include "util.h"
#include "stdio.h"

uint8_t brightness = 0;

rgbled_color_t getCurrentColor(void) {
    return (rgbled_color_t){ rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val()};
}

void stepBrightness(void) {
    if(brightness == 0) brightness = BRIGHTNESS_STEP;
    else brightness--;
    rgbled_color_t current = getCurrentColor();
    rgblight_sethsv_noeeprom(current.hue, current.sat, RGBLIGHT_LIMIT_VAL/BRIGHTNESS_STEP*brightness);
    rgblight_set();
}

void dumpCurrentLedColor(void) {
    char str[15] = {'\0'};
    rgbled_color_t current = getCurrentColor();
    sprintf(str, "%d/%d/%d ", current.hue, current.sat, current.val);
    send_string(str);
}
