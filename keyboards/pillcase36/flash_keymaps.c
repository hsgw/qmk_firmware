#include "flash_keymaps.h"

#define KEYMAP_SECTION_SIZE 0x800
#define KEYMAP_SECTION_START 0x0801F000

keymap_status KEYMAP_write(uint16_t* keymap, uint16_t length) {
  if (length > KEYMAP_SECTION_SIZE / 2) return KEYMAP_TOO_LONG_LENGTH;

  FLASH_Status status = FLASH_ErasePage(KEYMAP_SECTION_START);
  if (status != FLASH_COMPLETE) return KEYMAP_ERROR_ERASE;

  for (uint16_t i = 0; i < length; i++) {
    status = FLASH_ProgramHalfWord(KEYMAP_SECTION_START + i, keymap[i]);
    if (status != FLASH_COMPLETE) return KEYMAP_ERROR_WRITE;
  }

  return KEYMAP_COMPLETE;
}
