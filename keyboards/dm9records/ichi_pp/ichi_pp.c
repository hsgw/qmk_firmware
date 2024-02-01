// Copyright 2024 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ichi_pp.h"

void keyboard_pre_init_kb() {
    // Enable USB pins
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;
    keyboard_pre_init_user();
}
