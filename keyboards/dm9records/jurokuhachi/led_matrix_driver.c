// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lp5868-mono.h"
#include "led_matrix.h"

const led_matrix_driver_t led_matrix_driver = {
    .init          = lp5868_init,
    .set_value     = lp5868_set_value,
    .set_value_all = lp5868_set_value_all,
    .flush         = lp5868_flush,
};
