#pragma once

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP27
#define I2C1_SDA_PIN GP26
#define I2C1_SCL_SPEED 100000

// Enable this to use debug features (delayed init, console logs).
// Requires CONSOLE_ENABLE = yes in rules.mk
#define KNOT_C_DEBUG
