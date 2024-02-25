// Copyright 2024 Takuya Urakawa (@hsgw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LED_PINS \
    { GP28, GP29 }

//  Haptic feedback
#define SOLENOID_PIN GP1
#define SOLENOID_DEFAULT_DWELL 30

#define DIP_SWITCH_MATRIX_GRID \
    {                          \
        { 0, 0 }               \
    }

/*
 * You should define default led mode in keymaps/config.h
 * select below modes
 *
 * FR_LED_NO, FR_LED_CAPSLOCK, FR_LED_NUMLOCK, FR_LED_SOLENOID, FR_LED_LAYER
 *
 * FR_LED_LAYER = LAYER0
 * FR_LED_LAYER + 1 = LAYER1
 * .....
 *
 * #define DEFAULT_LED0_MODE FR_LEDMODE_NUMLOCK
 * #define DEFAULT_LED1_MODE FR_LEDMODE_SOLENOID
 * #define DEFAULT_HAPTIC_LED_NO 1
 * // if disable haptic led
 * // #define DEFAULT_HAPTIC_LED_NO -1
 */

#ifndef DEFAULT_LED0_MODE
#    define DEFAULT_LED0_MODE FR_LEDMODE_NUMLOCK
#endif

#ifndef DEFAULT_LED1_MODE
#    define DEFAULT_LED1_MODE FR_LEDMODE_SOLENOID
#endif

#ifndef DEFAULT_HAPTIC_LED_NO
#    define DEFAULT_HAPTIC_LED_NO 1
#endif

// Disable all dynamic led mode
// #define FRANNEL_DISABLE_DYNAMIC_LED_MODE

#ifndef TYPE_LED_DWELL
#    define TYPE_LED_DWELL 20
#endif
