// Copyright 2026 Takuya Urakawa @hsgw (5z6p.ccom)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * Initialize the CY8CMBR3108 touch sensor.
 * Verifies IDs and updates configuration if necessary.
 */
void cy8cmbr3108_init(void);

/**
 * Read the current button status from the sensor.
 * @return 16-bit status word where each bit represents a button.
 */
uint16_t cy8cmbr3108_read(void);

/**
 * Check if the sensor has been successfully initialized.
 * @return true if initialized and ready to be read.
 */
bool cy8cmbr3108_is_ready(void);
