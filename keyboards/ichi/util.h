#pragma once
#include "quantum.h"

typedef struct {
    uint8_t hue, sat, val;
} rgbled_color_t;

extern uint8_t brightness;

rgbled_color_t get_current_color(void);
void set_brightness(uint8_t val);
void step_brightness(void);
void dump_current_color(void);
