// Copyright 2026 Takuya Urakawa (@hsgw 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "lp5868.h"

void housekeeping_task_kb(void) {
    lp5868_task();
    housekeeping_task_user();
}
