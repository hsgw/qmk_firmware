#include "eeprom_ext.h"

#include "ch.h"
#include "hal.h"
#include "print.h"

#ifndef EEPROM_ADDRESS_SETTING
  #define EEPROM_ADDRESS_SETTING 0
#endif

#define EEPROM_ADDRESS  (0xA0 & EEPROM_ADDRESS_SETTING)
#define EEPROM_TIMEOUT  500

int16_t EEPROM_write(uint16_t start, uint8_t* send_data, uint16_t length) {
  uint8_t complete_packet[length+2];

  for(uint8_t i=0; i<length; i++) {
    complete_packet[i+2] = send_data[i];
  }

  complete_packet[0] = start >> 8;
  complete_packet[1] = start & 0xFF;
  // i2cStart(EEPROM_i2cd, EEPROM_i2ccfg);
  i2cAcquireBus(EEPROM_i2cd);
  int16_t ret = i2cMasterTransmitTimeout(EEPROM_i2cd, (EEPROM_ADDRESS >> 1), complete_packet, length+2, 0, 0, MS2ST(EEPROM_TIMEOUT));
  i2cReleaseBus(EEPROM_i2cd);
  // i2cStop(EEPROM_i2cd);
  printf("Write status: %d, i2cd Status: %d, cfg: %ld\n", (int16_t)ret, EEPROM_i2cd->state, *EEPROM_i2ccfg);

  return ret;
}


int16_t EEPROM_read(uint16_t start, uint8_t* recieved_data, uint16_t length) {
  uint8_t reg_address[2];

  reg_address[0] = start >> 8;
  reg_address[1] = start & 0xFF;
  // i2cStart(EEPROM_i2cd, EEPROM_i2ccfg);
  i2cAcquireBus(EEPROM_i2cd);
  int16_t ret = i2cMasterTransmitTimeout(EEPROM_i2cd, (EEPROM_ADDRESS >> 1), reg_address, 2, recieved_data, length, MS2ST(EEPROM_TIMEOUT));
  i2cReleaseBus(EEPROM_i2cd);
  printf("Read status: %d, i2cd Status: %d, cfg: %ld\n", (int16_t)ret, EEPROM_i2cd->state, &EEPROM_i2ccfg);
  // i2cStop(EEPROM_i2cd);
  return ret;
}

uint8_t 	eeprom_read_byte (const uint8_t *__p) {
  const uint16_t address = (const uint32_t) __p;
  uint8_t ret;
  EEPROM_read(address, &ret, 1);
  return ret;
}

uint16_t 	eeprom_read_word (const uint16_t *__p) {
  const uint16_t address = (const uint32_t) __p;
  uint8_t temp[2];
  EEPROM_read(address, temp, 2);
  return temp[0] | (temp[1] << 8);
}

uint32_t 	eeprom_read_dword (const uint32_t *__p) {
  const uint16_t address = (const uint32_t) __p;
  uint8_t temp[4];
  EEPROM_read(address, temp, 4);
  return temp[0] | (((uint32_t)temp[1]) << 8) | (((uint32_t)temp[2]) << 16) | (((uint32_t)temp[3]) << 24);
}

void 	eeprom_read_block (void *__dst, const void *__src, uint32_t __n){

}

void 	eeprom_write_byte (uint8_t *__p, uint8_t __value) {
  uint16_t address = (uint32_t)__p;
  EEPROM_write(address, &__value, 1);
}

void 	eeprom_write_word (uint16_t *__p, uint16_t __value){
  uint16_t address = (uint32_t)__p;
  uint8_t temp[2] = { (uint8_t)(__value & 0xFF), (uint8_t)(__value >> 8) };
  EEPROM_write(address, temp, 2);
}

void 	eeprom_write_dword (uint32_t *__p, uint32_t __value){
  uint16_t address = (uint32_t)__p;
  uint8_t temp[4] =  {
    (uint8_t)(__value & 0xFF),
    (uint8_t)((__value >> 8) & 0xFF),
    (uint8_t)((__value >> 16) & 0xFF),
    (uint8_t)(__value >> 24)
  };
  EEPROM_write(address, temp, 4);
}

void 	eeprom_write_block (const void *__src, void *__dst, uint32_t __n){

}

void 	eeprom_update_byte (uint8_t *__p, uint8_t __value){
  uint16_t address = (uint32_t)__p;
  uint8_t temp;
  EEPROM_read(address, &temp, 1);
  if (temp != __value) {
    EEPROM_write(address, &temp, 1);
  }
}

void 	eeprom_update_word (uint16_t *__p, uint16_t __value){
  uint16_t address = (uint32_t)__p;
  uint8_t value[2] = { (uint8_t)(__value & 0xFF), (uint8_t)(__value >> 8) };
  uint8_t temp;
  for(uint8_t i=0; i<2; i++) {
    EEPROM_read(address, &temp, 1);
    if (temp != value[i]) {
      EEPROM_write(address, &temp, 1);
    }
  }
}

void 	eeprom_update_dword (uint32_t *__p, uint32_t __value){
  uint16_t address = (uint32_t)__p;
  uint8_t value[4] =  {
    (uint8_t)(__value & 0xFF),
    (uint8_t)((__value >> 8) & 0xFF),
    (uint8_t)((__value >> 16) & 0xFF),
    (uint8_t)(__value >> 24)
  };
  uint8_t temp;
  for(uint8_t i=0; i<4; i++) {
    EEPROM_read(address, &temp, 1);
    if (temp != value[i]) {
      EEPROM_write(address, &temp, 1);
    }
  }
}

void 	eeprom_update_block (const void *__src, void *__dst, uint32_t __n){

}

