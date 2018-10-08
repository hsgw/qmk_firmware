#include "i2c_stm32.h"

#include "ch.h"
#include "hal.h"
#include "print.h"
#include "i2c_stm32.h"

I2CConfig i2c1cfg = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

// I2CConfig i2c1cfg = {
//      OPMODE_I2C,
//      100000,
//      STD_DUTY_CYCLE
// };

I2CDriver* EEPROM_i2cd = &I2CD1;
I2CConfig* EEPROM_i2ccfg = &i2c1cfg;

void i2c_init(void) {
  palSetGroupMode(GPIOB, 6 | 7, 0, PAL_MODE_INPUT); // Try releasing special pins for a short time
  chThdSleepMilliseconds(10);

  i2cStart(&I2CD1, &i2c1cfg);
  palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
  palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
}
