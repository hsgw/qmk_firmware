// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// 74HC138 (Decoder) pins
// Assuming 3 address pins for 8 rows
#define HC138_ADDR_0 GP13
#define HC138_ADDR_1 GP14
#define HC138_ADDR_2 GP15

// 74HC165 (PISO Shift Register) pins
// Assuming two 74HC165 in series for 16 columns
#define HC165_LATCH GP10 // Latch pin (PL)
#define HC165_CLOCK GP9  // Clock pin (CP)
#define HC165_DATA GP11  // Data pin for the 74HC165 chain (QH)

// SPI Configuration
#define SPI_DRIVER SPID0 // SPI0

#define SPI_SCK_PIN GP6
#define SPI_SCK_PAL_MODE 1

#define SPI_MOSI_PIN GP7
#define SPI_MOSI_PAL_MODE 1

#define SPI_MISO_PIN GP4
#define SPI_MISO_PAL_MODE 1

// LP5868 VSYNC pin
#define LP5868_VSYNC_PIN GP8
#define LP5868_CS_PIN GP3

// LED Matrix configuration
#define LED_MATRIX_DEFAULT_ON true
#define LED_MATRIX_DEFAULT_MODE LED_MATRIX_SOLID
