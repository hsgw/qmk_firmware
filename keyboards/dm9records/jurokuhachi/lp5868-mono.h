// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

// LP5868 Register Definitions
#define REG_CHIP_EN 0x000
#define REG_DEV_INITIAL 0x001
#define REG_DEV_CONFIG1 0x002
#define REG_DEV_CONFIG2 0x003
#define REG_DEV_CONFIG3 0x004
#define REG_SW_RESET 0x005
#define REG_RGB_CURRENT 0x006
#define REG_GLOBAL_BRI 0x009
#define REG_PWM_BRI_BASE 0x00A
#define REG_DOT_CURRENT_BASE 0x0C0

#define LP5868_DRIVER_WIDTH 18
#define LP5868_DRIVER_HEIGHT 8
#define LP5868_BYTES_PER_DRIVER (LP5868_DRIVER_WIDTH * LP5868_DRIVER_HEIGHT)

void lp5868_init(void);
void lp5868_set_value(int index, uint8_t value);
void lp5868_set_value_all(uint8_t value);
void lp5868_flush(void);
void lp5868_task(void);
