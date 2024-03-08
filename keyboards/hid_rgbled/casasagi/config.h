// Copyright 2024 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define SERIAL_USART_DRIVER SD1    // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 0 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 10

/* i2c settings */
#define I2C_DRIVER I2CD2
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

// SPI
#define WS2812_SPI_DRIVER SPID2
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PAL_MODE 0
#define WS2812_SPI_SCK_PIN B13
#define WS2812_EXTERNAL_PULLUP

#define RGBLIGHT_DEFAULT_ON true
