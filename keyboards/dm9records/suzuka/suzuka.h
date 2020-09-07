/* Copyright 2020 Takuya Urakawa (dm9records.com 5z6p.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
// clang-format off
#define LAYOUT( \
    kl00,       kl02, kl03, kl04, kl05,     kr00, kr01, kr02, kr03, kr04, kr05, kr06, kr07, kr08, kr09, kr39, \
    kl10, kl11, kl12, kl13, kl14, kl15,     kr10, kr11, kr12, kr13, kr14, kr15, kr16, kr17, kr18, kr28, kr19, kr49,\
    kl20, kl21, kl22, kl23, kl24, kl25,     kr20, kr21, kr22, kr23, kr24, kr25, kr26, kr27, kr38, kr29, kr59, \
    kl30, kl31, kl32, kl33, kl34, kl35,     kr30, kr31, kr32, kr33, kr34, kr35, kr36, \
    kl40, kl41, kl42, kl43, kl44, kl45,     kr40, kr41, kr42, kr43, kr44, kr45, kr46, kr47, \
    kl50, kl51, kl52, kl53, kl54,           kr50, kr51, kr52, kr53, kr54, kr55, kr56, kr57, kr58 \
) \
{ \
    { kl00,   KC_NO,  kl02,   kl03,   kl04,   kl05,   KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
    { kl10,   kl11,   kl12,   kl13,   kl14,   kl15,   KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
    { kl20,   kl21,   kl22,   kl23,   kl24,   kl25,   KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
    { kl30,   kl31,   kl32,   kl33,   kl34,   kl35,   KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
    { kl40,   kl41,   kl42,   kl43,   kl44,   kl45,   KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
    { kl50,   kl51,   kl52,   kl53,   kl54,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
\
    { kr00,   kr01,   kr02,   kr03,   kr04,   kr05,   kr06,   kr07,   kr08,   kr09 }, \
    { kr10,   kr11,   kr12,   kr13,   kr14,   kr15,   kr16,   kr17,   kr18,   kr19 }, \
    { kr20,   kr21,   kr22,   kr23,   kr24,   kr25,   kr26,   kr27,   kr28,   kr29 }, \
    { kr30,   kr31,   kr32,   kr33,   kr34,   kr35,   kr36,   KC_NO,  kr38,   kr39 }, \
    { kr40,   kr41,   kr42,   kr43,   kr44,   kr45,   kr46,   kr47,   KC_NO,  kr49 }, \
    { kr50,   kr51,   kr52,   kr53,   kr54,   kr55,   kr56,   kr57,   kr58,   kr59 } \
}
// clang-format on
