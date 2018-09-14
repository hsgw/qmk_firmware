#pragma once
#include <ch.h>

void ext_eeprom_init(void);
int16_t ext_eeprom_write(uint16_t start, uint8_t* send_data, uint16_t length);
int16_t ext_eeprom_read(uint16_t start, uint8_t* recieved_data, uint16_t length);
