#include "eeprom_ext_test.h"

#include "ch.h"
#include "hal.h"

#include <string.h>


#ifndef EEPROM_TEST_ADDRESS_SETTING
  #define EEPROM_TEST_ADDRESS_SETTING 0
#endif

#define EEPROM_TEST_ADDRESS  (0xA2)
#define EEPROM_TEST_TIMEOUT  100

int16_t EEPROM_TEST_write_raw(uint8_t* send_data, uint16_t length) {
  i2cAcquireBus(EEPROM_i2cd);
  i2cStart(EEPROM_i2cd, EEPROM_i2ccfg);
  int16_t ret = i2cMasterTransmitTimeout(EEPROM_i2cd, (EEPROM_TEST_ADDRESS >> 1), send_data, length, 0, 0, MS2ST(EEPROM_TEST_TIMEOUT));
  i2cReleaseBus(EEPROM_i2cd);
  // i2cStop(EEPROM_i2cd);

  return ret;
}

int16_t EEPROM_TEST_write(uint16_t start, uint8_t* send_data, uint16_t length) {
  uint8_t packet[length+2];

  memcpy(packet+2, send_data, length);

  packet[0] = start >> 8;
  packet[1] = start & 0xFF;

  int16_t ret =EEPROM_TEST_write_raw(packet, length + 2);
  chThdSleepMilliseconds(5);
  return ret;

}

int16_t EEPROM_TEST_read(uint16_t start, uint8_t* recieved_data, uint16_t length) {
  uint8_t reg_address[2];

  reg_address[0] = start >> 8;
  reg_address[1] = start & 0xFF;
  i2cAcquireBus(EEPROM_i2cd);
  i2cStart(EEPROM_i2cd, EEPROM_i2ccfg);
  int16_t ret = i2cMasterTransmitTimeout(EEPROM_i2cd, (EEPROM_TEST_ADDRESS >> 1), reg_address, 2, recieved_data, length, MS2ST(EEPROM_TEST_TIMEOUT));
  i2cReleaseBus(EEPROM_i2cd);
  // i2cStop(EEPROM_i2cd);

  return ret;
}
