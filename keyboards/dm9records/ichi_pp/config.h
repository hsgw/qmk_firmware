// Copyright 2023 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

// SPI
#define WS2812_SPI_DRIVER SPID1
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PAL_MODE 0
#define WS2812_SPI_SCK_PIN A5
#define WS2812_EXTERNAL_PULLUP
