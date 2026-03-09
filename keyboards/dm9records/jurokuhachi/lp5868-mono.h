// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

void lp5868_init(void);
void lp5868_set_value(int index, uint8_t value);
void lp5868_set_value_all(uint8_t value);
void lp5868_flush(void);
void lp5868_task(void);
