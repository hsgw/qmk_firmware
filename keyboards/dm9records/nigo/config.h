// Copyright 2023 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

// i2c EEPROM config
#define I2C1_SCL_PIN F1
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PIN F0
#define I2C1_SDA_PAL_MODE 1

#define EEPROM_I2C_24LC64
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10101110
