#pragma once

#include "flash_stm32.h"

typedef enum {
  KEYMAP_TOO_LONG_LENGTH = 1,
  KEYMAP_ERROR_ERASE,
  KEYMAP_ERROR_WRITE,
  KEYMAP_COMPLETE = 5,
} keymap_status;

keymap_status KEYMAP_write(uint16_t* keymap, uint16_t length);
