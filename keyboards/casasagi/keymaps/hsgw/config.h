/*
Copyright 2021 Takuya Urakawa(hsgw)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#undef VENDOR_ID
#undef PRODUCT_ID
#define VENDOR_ID 0xCA5A
#define PRODUCT_ID 0x5A61

/* VIA setting */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 1
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 1

#define TAPPING_TERM 150
#define TAPPING_TOGGLE 2

#define RETRO_TAPPING
