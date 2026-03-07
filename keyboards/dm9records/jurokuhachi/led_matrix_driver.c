// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lp5868.h"
#include "led_matrix.h"

static void init(void) {
    lp5868_init();
}

static void set_value(int index, uint8_t value) {
    uint8_t row = index / LED_MATRIX_COLS;
    uint8_t col = index % LED_MATRIX_COLS;
    lp5868_set_pixel(col, row, value);
}

static void set_value_all(uint8_t value) {
    lp5868_fill_pixel(value);
}

static void flush(void) {
    lp5868_update();
}

const led_matrix_driver_t led_matrix_driver = {
    .init = init,
    .set_value = set_value,
    .set_value_all = set_value_all,
    .flush = flush,
};
