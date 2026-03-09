// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef KEYBOARD_dm9records_jurokuhachi_256
// 256-key revision specific settings
#    define JUROKUHACHI_256
#    define LP5868_DRIVER_COUNT 2
#    define LP5868_CS_PINS \
        { GP3, GP26 }
#else
// Default to 128-key revision
#    define LP5868_DRIVER_COUNT 1
#    define LP5868_CS_PINS \
        { GP3 }
#endif

// 74HC138 (Decoder) pins
#define HC138_ADDR_0 GP13
#define HC138_ADDR_1 GP14
#define HC138_ADDR_2 GP15

// 74HC165 (PISO Shift Register) pins
#define HC165_LATCH GP10  // Latch pin (PL)
#define HC165_CLOCK GP9   // Clock pin (CP)
#define HC165_DATA GP11   // Data pin for the 74HC165 chain (QH)
#define HC165_DATA_2 GP12 // Additional data pin for 256-key config

// SPI Configuration
#define SPI_DRIVER SPID0 // SPI0
#define SPI_SCK_PIN GP6
#define SPI_SCK_PAL_MODE 1
#define SPI_MOSI_PIN GP7
#define SPI_MOSI_PAL_MODE 1
#define SPI_MISO_PIN GP4
#define SPI_MISO_PAL_MODE 1

// LP5868 configuration
#define LP5868_VSYNC_PIN GP8

// LED Matrix configuration
#define LED_MATRIX_ROWS MATRIX_ROWS
#define LED_MATRIX_COLS MATRIX_COLS
#define LED_MATRIX_DEFAULT_ON true
#define LED_MATRIX_DEFAULT_MODE LED_MATRIX_SOLID
