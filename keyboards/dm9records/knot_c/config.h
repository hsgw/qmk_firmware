#pragma once

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP27
#define I2C1_SDA_PIN GP26
#define I2C1_SCL_SPEED 100000

/* Pointing Device */
#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_INVERT_X

/* PMW3610 */
#define PMW3610_CS_PIN GP13
#define PMW3610_SCLK_PIN GP12
#define PMW3610_SDIO_PIN GP11

// Enable this to use debug features (delayed init, console logs).
// Requires CONSOLE_ENABLE = yes in rules.mk
#define KNOT_C_DEBUG
