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
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
