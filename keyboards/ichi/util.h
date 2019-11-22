#pragma once
#include "quantum.h"

typedef struct {
    uint8_t hue, sat, val;
} rgbled_color_t;

extern uint8_t brightness;

rgbled_color_t getCurrentColor(void);
void stepBrightness(void);
void dumpCurrentLedColor(void);
