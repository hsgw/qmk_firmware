#pragma once

#include <quantum.h>

void frannel_led_set(uint8_t no, bool state);
void frannel_led_toggle_temp(uint8_t no);
void frannel_led_restore(void);
bool frannel_led_get_state(uint8_t no);

void frannel_haptic_led_enable(bool flag);
void frannel_solenoid_enable(bool flag);

#ifdef FRANNEL_DISABLE_DYNAMIC_LED_MODE
#    define FRANNEL_SAFE_RANGE SAFE_RANGE
#else
enum frannnel_keycode {
    FR_LED0_NO = SAFE_RANGE,
    FR_LED0_CAPS,
    FR_LED0_NUM,
    FR_LED0_SOL,
    FR_LED0_L0,
    FR_LED0_L1,
    FR_LED0_L2,
    FR_LED0_L3,
    FR_LED0_L4,
    FR_LED0_L5,
    FR_LED1_NO,
    FR_LED1_CAPS,
    FR_LED1_NUM,
    FR_LED1_SOL,
    FR_LED1_L0,
    FR_LED1_L1,
    FR_LED1_L2,
    FR_LED1_L3,
    FR_LED1_L4,
    FR_LED1_L5,
    FR_HAPLED_NO,
    FR_HAPLED_0,
    FR_HAPLED_1,
};

#    define FL_NO(no) FR_LED##no##_NO
#    define FL_CA(no) FR_LED##no##_CAPS
#    define FL_NU(no) FR_LED##no##_NUM
#    define FL_SO(no) FR_LED##no##_SOL
#    define FL_L(no, layer) FR_LED##no##_L##layer

#    define FL_HPL_NO FR_HAPLED_NO
#    define FL_HPL(no) FR_HAPLED_##no

#    define FRANNEL_SAFE_RANGE FR_HAPLED_1 + 1

enum frannel_led_mode {
    FR_LED_NO = 0,
    FR_LED_CAPSLOCK,
    FR_LED_NUMLOCK,
    FR_LED_SOLENOID,
    FR_LED_LAYER,
};

void frannel_led_mode_set_noeeprom(uint8_t no, uint8_t mode);
void frannel_led_mode_set(uint8_t no, uint8_t mode);

void frannel_haptic_led_set_noeeprom(int8_t no);
void frannel_haptic_led_set(int8_t no);
#endif
