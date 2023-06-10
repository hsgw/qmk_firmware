/* Copyright 2023 hsgw (Takuya Urakawa, Dm9Records, 5z6p.com)
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

#include "goni.h"

void keyboard_pre_init_kb() {
    // Enable USB pins
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;
    keyboard_pre_init_user();
}
