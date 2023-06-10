// Copyright 2023 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define I2C1_SCL_PIN F1
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PIN F0
#define I2C1_SDA_PAL_MODE 1
