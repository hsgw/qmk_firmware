/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include "maple_test.h"
#include "ext_eeprom.h"

#include <print.h>
#include <wait.h>

enum custom_keycode {
  CK_BOOT = SAFE_RANGE
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{RESET}},
};

void matrix_init_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    default:
      return true;
  }
}

static const WDGConfig wdgcfg = {
  STM32_IWDG_PR_4,
  STM32_IWDG_RL(100)
};

// magic word for enter bootloader when next reset
#define RTC_BOOTLOADER_FLAG 0x424C

// write magic word to RTC backup register(not clear when reset)
void bkp10Write(uint16_t value)
{
  // Enable clocks for the backup domain registers
  RCC->APB1ENR |= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);

  // Disable backup register write protection
  PWR->CR |= PWR_CR_DBP;

  // store value in pBK DR10
  BKP->DR10 = value;

  // Re-enable backup register write protection
  PWR->CR &=~ PWR_CR_DBP;
}

// call from "RESET" keycode action
void bootloader_jump(void) {
  bkp10Write(RTC_BOOTLOADER_FLAG);
  wdgInit();
  wdgStart(&WDGD1, &wdgcfg);
  while(1) {}
}
