#include "ext_eeprom.h"

#include <ch.h>
#include <hal.h>
#include <print.h>

#ifndef EEPROM_ADDRESS_SETTING
  #define EEPROM_ADDRESS_SETTING 0
#endif

#define EEPROM_ADDRESS  0xA0
#define EEPROM_TIMEOUT  1000

static const I2CConfig i2ccfg = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

void ext_eeprom_init(void) {
  palSetGroupMode(GPIOB, 6 | 7, 0, PAL_MODE_INPUT); // Try releasing special pins for a short time
  chThdSleepMilliseconds(10);

  i2cStart(&I2CD1, &i2ccfg);
  palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
}

int16_t ext_eeprom_write(uint16_t start, uint8_t* send_data, uint16_t length) {
  uint8_t complete_packet[length+2];

  for(uint8_t i=0; i<length; i++) {
    complete_packet[i+2] = send_data[i];
  }

  complete_packet[0] = start >> 8;
  complete_packet[1] = start & 0xFF;
  // i2cStart(&I2CD1, &i2ccfg);
  i2cAcquireBus(&I2CD1);
  uint16_t ret = i2cMasterTransmitTimeout(&I2CD1, (EEPROM_ADDRESS >> 1), complete_packet, length+2, 0, 0, MS2ST(EEPROM_TIMEOUT));
  i2cReleaseBus(&I2CD1);
  // i2cStop(&I2CD1);

  return ret;
}


int16_t ext_eeprom_read(uint16_t start, uint8_t* recieved_data, uint16_t length) {
  uint8_t reg_address[2];

  reg_address[0] = start >> 8;
  reg_address[1] = start & 0xFF;
  // i2cStart(&I2CD1, &i2ccfg);
  i2cAcquireBus(&I2CD1);
  uint16_t ret = i2cMasterTransmitTimeout(&I2CD1, (EEPROM_ADDRESS >> 1), reg_address, 2, recieved_data, length, MS2ST(EEPROM_TIMEOUT));
  i2cReleaseBus(&I2CD1);
  // i2cStop(&I2CD1);
  return ret;
}
