/* Copyright 2021 SMKiJ Casasagi Contributors
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

#include "casasagi.h"

void board_init(void) {
    // remap dma channel for SPI2
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_SPI2_DMA_RMP;

    setPinInputHigh(SPLIT_HAND_PIN);
}

bool is_keyboard_left(void) {
    return readPin(SPLIT_HAND_PIN);
}
