#pragma once

#include <stdint.h>

#include "hal.h"

extern I2CDriver* EEPROM_i2cd;
extern I2CConfig* EEPROM_i2ccfg;

int16_t EEPROM_TEST_write_raw(uint8_t* send_data, uint16_t length);
int16_t EEPROM_TEST_write(uint16_t start, uint8_t* send_data, uint16_t length);
int16_t EEPROM_TEST_read(uint16_t start, uint8_t* recieved_data, uint16_t length);
int16_t EEPROM_TEST_update(uint16_t start, uint8_t* recieved_data, uint16_t length);

/*
decration in eeprom.h

uint8_t 	eeprom_read_byte (const uint8_t *__p);
uint16_t 	eeprom_read_word (const uint16_t *__p);
uint32_t 	eeprom_read_dword (const uint32_t *__p);
void 	eeprom_read_block (void *__dst, const void *__src, uint32_t __n);
void 	eeprom_write_byte (uint8_t *__p, uint8_t __value);
void 	eeprom_write_word (uint16_t *__p, uint16_t __value);
void 	eeprom_write_dword (uint32_t *__p, uint32_t __value);
void 	eeprom_write_block (const void *__src, void *__dst, uint32_t __n);
void 	eeprom_update_byte (uint8_t *__p, uint8_t __value);
void 	eeprom_update_word (uint16_t *__p, uint16_t __value);
void 	eeprom_update_dword (uint32_t *__p, uint32_t __value);
void 	eeprom_update_block (const void *__src, void *__dst, uint32_t __n);
*/
