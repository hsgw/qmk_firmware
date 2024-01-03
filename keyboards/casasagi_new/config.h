// Copyright 2024 Takuya Urakawa (@hsgw)
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

#define SERIAL_USART_DRIVER SD1    // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 0 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 10

/* i2c settings */
#define I2C_DRIVER I2CD2
// #define I2C1_SCL_BANK GPIOB
// #define I2C1_SCL 10
// #define I2C1_SDA_BANK GPIOB
// #define I2C1_SDA 11
#define I2C1_SCL_PIN B10
#define I2C1_SDA_PIN B11
#define I2C1_TIMINGR_PRESC 2U
#define I2C1_TIMINGR_SCLDEL 1U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 9U
#define I2C1_TIMINGR_SCLL 26U
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define EEPROM_I2C_24LC64
