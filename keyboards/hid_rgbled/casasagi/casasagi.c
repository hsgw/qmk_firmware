// Copyright 2024 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void board_init(void) {
    // remap dma channel for SPI2
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_SPI2_DMA_RMP;
}

void keyboard_pre_init_kb() {
    // setPinInputHigh(SPLIT_HAND_PIN);
    keyboard_pre_init_user();
}
