#pragma once

#include <quantum.h>

enum { FR_LED_NO = 0, FR_LED_CAPSLOCK, FR_LED_NUMLOCK, FR_LED_SOLENOID, FR_LED_LAYER };

void frannel_led_set(uint8_t no, bool state);
void frannel_led_toggle_temp(uint8_t no);
void frannel_led_restore(void);

bool frannel_led_get_state(uint8_t no);

void frannel_enable_solenoid(bool flag);
void frannel_enable_haptic_led(bool flag);

void frannel_set_led_mode_noeeprom(uint8_t no, uint8_t mode);
void frannel_set_led_mode(uint8_t no, uint8_t mode);

void frannel_set_haptic_led_noeeprom(int8_t no);
void frannel_set_haptic_led(int8_t no);

void frannel_update_host_leds(led_t led_state);
void frannel_update_layer_leds(layer_state_t state);
void frannel_update_solenoid_leds(void);
