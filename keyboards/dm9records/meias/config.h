// Copyright 2024 Takuya Urakawa (@hsgw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* usart settings for split */
#define SERIAL_USART_DRIVER SD1    // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 1 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 10

/* i2c settings for EEPROM */
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B13
#define I2C1_SDA_PIN B14
#define I2C1_SCL_PAL_MODE 5
#define I2C1_SDA_PAL_MODE 5

#define EEPROM_I2C_24LC64
