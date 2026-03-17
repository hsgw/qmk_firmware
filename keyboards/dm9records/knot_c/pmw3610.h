// This code is based on https://github.com/inorichi/zmk-pmw3610-driver
#pragma once

#include "keyboard.h"
#include <stdint.h>
#include "util.h"
#include "pointing_device.h"
#include "gpio.h"

// Register addresses

/* Sensor registers (addresses) */
#define PMW3610_REG_PRODUCT_ID 0x00
#define PMW3610_REG_REVISION_ID 0x01
#define PMW3610_REG_MOTION 0x02
#define PMW3610_REG_DELTA_X_L 0x03
#define PMW3610_REG_DELTA_Y_L 0x04
#define PMW3610_REG_DELTA_XY_H 0x05
#define PMW3610_REG_SQUAL 0x06
#define PMW3610_REG_SHUTTER_HIGHER 0x07
#define PMW3610_REG_SHUTTER_LOWER 0x08
#define PMW3610_REG_PIX_MAX 0x09
#define PMW3610_REG_PIX_AVG 0x0A
#define PMW3610_REG_PIX_MIN 0x0B

#define PMW3610_REG_CRC0 0x0C
#define PMW3610_REG_CRC1 0x0D
#define PMW3610_REG_CRC2 0x0E
#define PMW3610_REG_CRC3 0x0F
#define PMW3610_REG_SELF_TEST 0x10

#define PMW3610_REG_PERFORMANCE 0x11
#define PMW3610_REG_MOTION_BURST 0x12

#define PMW3610_REG_RUN_DOWNSHIFT 0x1B
#define PMW3610_REG_REST1_PERIOD 0x1C
#define PMW3610_REG_REST1_DOWNSHIFT 0x1D
#define PMW3610_REG_REST2_PERIOD 0x1E
#define PMW3610_REG_REST2_DOWNSHIFT 0x1F
#define PMW3610_REG_REST3_PERIOD 0x20
#define PMW3610_REG_OBSERVATION 0x2D

#define PMW3610_REG_PIXEL_GRAB 0x35
#define PMW3610_REG_FRAME_GRAB 0x36

#define PMW3610_REG_POWER_UP_RESET 0x3A
#define PMW3610_REG_SHUTDOWN 0x3B

#define PMW3610_REG_SPI_CLK_ON_REQ 0x41
#define PMW3610_REG_RES_STEP 0x85

#define PMW3610_REG_NOT_REV_ID 0x3E
#define PMW3610_REG_NOT_PROD_ID 0x3F

#define PMW3610_REG_PRBS_TEST_CTL 0x47
#define PMW3610_REG_SPI_PAGE0 0x7F
#define PMW3610_REG_VCSEL_CTL 0x9E
#define PMW3610_REG_LSR_CONTROL 0x9F
#define PMW3610_REG_SPI_PAGE1 0xFF

/* Sensor identification values */
#define PMW3610_PRODUCT_ID 0x3E

/* Power-up register commands */
#define PMW3610_POWERUP_CMD_RESET 0x5A
#define PMW3610_POWERUP_CMD_WAKEUP 0x96

/* spi clock enable/disable commands */
#define PMW3610_SPI_CLOCK_CMD_ENABLE 0xBA
#define PMW3610_SPI_CLOCK_CMD_DISABLE 0xB5

/* Max register count readable in a single motion burst */
#define PMW3610_MAX_BURST_SIZE 10

/* Register count used for reading a single motion burst */
#define PMW3610_BURST_SIZE 7

/* Position in the motion registers */
#define PMW3610_X_L_POS 1
#define PMW3610_Y_L_POS 2
#define PMW3610_XY_H_POS 3
#define PMW3610_SHUTTER_H_POS 5
#define PMW3610_SHUTTER_L_POS 6

#define PMW3610_MOTION_BIT 0x80

/* cpi/resolution range */
#define PMW3610_MAX_CPI 3200
#define PMW3610_MIN_CPI 200
#define PMW3610_CPI_STEP 200

/* write command bit position */
#define PMW3610_SPI_WRITE_BIT 0x80

/* Helper macros used to convert sensor values. */
#define PMW3610_SVALUE_TO_CPI(svalue) ((uint32_t)(svalue).val1)
#define PMW3610_SVALUE_TO_TIME(svalue) ((uint32_t)(svalue).val1)

// #if defined(CONFIG_PMW3610_POLLING_RATE_250) || defined(CONFIG_PMW3610_POLLING_RATE_125_SW)
#define PMW3610_POLLING_RATE_VALUE 0x0D
// #elif defined(CONFIG_PMW3610_POLLING_RATE_125)
// #    define PMW3610_POLLING_RATE_VALUE 0x00
// #else
// #    error "A valid PMW3610 polling rate must be selected"
// #endif

// #ifdef CONFIG_PMW3610_FORCE_AWAKE
// #define PMW3610_FORCE_MODE_VALUE 0xF0
// #else
#define PMW3610_FORCE_MODE_VALUE 0x00
// #endif

#define PMW3610_PERFORMANCE_VALUE (PMW3610_FORCE_MODE_VALUE | PMW3610_POLLING_RATE_VALUE)

/* Timings (in us) used in SPI communication. Since MCU should not do other tasks during wait,
 * k_busy_wait is used instead of k_sleep */
// - sub-us time is rounded to us, due to the limitation of k_busy_wait, see :
// https://github.com/zephyrproject-rtos/zephyr/issues/6498
#define PMW3610_T_NCS_SCLK 1     /* 120 ns (rounded to 1us) */
#define PMW3610_T_SCLK_NCS_WR 10 /* 10 us */
#define PMW3610_T_SRAD 4         /* 4 us */
#define PMW3610_T_SRAD_MOTBR 4   /* same as T_SRAD */
#define PMW3610_T_SRX 1          /* 250 ns (rounded to 1 us) */
#define PMW3610_T_SWX 30         /* SWW: 30 us, SWR: 20 us */
#define PMW3610_T_BEXIT 1        /* 250 ns (rounded to 1us)*/

// qmk config

/*
 * CPI
 */
#ifndef PMW3610_CPI
#    define PMW3610_CPI 800U
#endif

/*
 * 3wire SPI
 */
// CS
#ifndef PMW3610_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define PMW3610_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No chip select pin defined -- missing PMW3610_CS_PIN or PMW3610_CS_PINS"
#    endif
#endif
#if !defined(PMW3610_CS_PIN_RIGHT)
#    define PMW3610_CS_PIN_RIGHT PMW3610_CS_PIN
#endif
// SCLK
#ifndef PMW3610_SCLK_PIN
#    ifdef POINTING_DEVICE_SCLK_PIN
#        define PMW3610_SCLK_PIN POINTING_DEVICE_SCLK_PIN
#    else
#        error "No SCL pin defined -- missing PMW3610_SCLK_PIN"
#    endif
#endif
#if !defined(PMW3610_SCLK_PIN_RIGHT)
#    define PMW3610_SCLK_PIN_RIGHT PMW3610_SCLK_PIN
#endif
// SDIO
#ifndef PMW3610_SDIO_PIN
#    ifdef POINTING_DEVICE_SDIO_PIN
#        define PMW3610_SDIO_PIN POINTING_DEVICE_SDIO_PIN
#    else
#        error "No SDIO pin defined -- missing PMW3610_SDIO_PIN"
#    endif
#endif
#if !defined(PMW3610_SDIO_PIN_RIGHT)
#    define PMW3610_SDIO_PIN_RIGHT PMW3610_SDIO_PIN
#endif
// optional
#ifndef PMW3610_MOTION_PIN
#    ifdef POINTING_DEVICE_MOTION_PIN
#        define PMW3610_MOTION_PIN POINTING_DEVICE_MOTION_PIN
#    endif
#endif
#ifdef PMW3610_MOTION_PIN
#    if !defined(PMW3610_MOTION_PIN_RIGHT)
#        define PMW3610_MOTION_PIN_RIGHT PMW3610_MOTION_PIN
#    endif
#endif

#ifndef PMW3610_REST1_SAMPLE_TIME_MS
#    define PMW3610_REST1_SAMPLE_TIME_MS 40
#endif
#ifndef PMW3610_REST2_SAMPLE_TIME_MS
#    define PMW3610_REST2_SAMPLE_TIME_MS 0
#endif

// qmk specific

#if PMW3610_CPI > PMW3610_MAX_CPI || PMW3610_CPI < PMW3610_MIN_CPI || (PMW3610_CPI % PMW3610_CPI_STEP) != 0U
#    pragma message "PMW3610_CPI has to be in the range of " STR(PMW3610_CPI_MAX) "-" STR(PMW3610_CPI_MIN) " in increments of " STR(PMW3610_CPI_STEP) ". But it is " STR(PMW3610_CPI) "."
#    error Use correct PMW3610_CPI value.
#endif

#define cs_pin (is_keyboard_left() ? PMW3610_CS_PIN : PMW3610_CS_PIN_RIGHT)
#define sclk_pin (is_keyboard_left() ? PMW3610_SCLK_PIN : PMW3610_SCLK_PIN_RIGHT)
#define sdio_pin (is_keyboard_left() ? PMW3610_SDIO_PIN : PMW3610_SDIO_PIN_RIGHT)
// #define motion_pin (is_keyboard_left() ? PMW3610_MOTION_PIN : PMW3610_MOTION_PIN_RIGHT)

const pointing_device_driver_t pmw3610_pointing_device_driver;

/**
 * @brief Initializes the given sensor so it is in a working state and ready to
 * be polled for data.
 *
 * @param sensor Index of the sensors chip select pin
 * @return true Initialization was a success
 * @return false Initialization failed, do not proceed operation
 */
bool __attribute__((cold)) pmw3610_init(uint8_t sensor);

/**
 * @brief Gets the currently set CPI value from the sensor. CPI is often
 * refereed to as the sensors sensitivity.
 *
 * @param sensor Index of the sensors chip select pin
 * @return uint16_t Current CPI value of the sensor
 */
uint16_t pmw3610_get_cpi(uint8_t sensor);

/**
 * @brief Sets the given CPI value for the given pmw3610 sensor. CIP is often
 * refereed to as the sensors sensitivity. Values outside of the allow range are
 * constrained into legal values.
 *
 * @param sensor Index of the sensors chip select pin
 * @param cpi CPI value to set, legal range depends on the PMW sensor type
 */
void pmw3610_set_cpi(uint8_t sensor, uint16_t cpi);

/**
 * @brief Read one byte of data from the given register on the sensor
 *
 * @param sensor Index of the sensors chip select pin
 * @param reg_addr Register address to read from
 * @return uint8_t
 */
uint8_t pmw3610_read(uint8_t sensor, uint8_t reg_addr);

/**
 * @brief Writes one byte of data to the given register on the sensor
 *
 * @param sensor Index of the sensors chip select pin
 * @param reg_addr Registers address to write to
 * @param data Data to write to the register
 * @return true Write was a success
 * @return false Write failed, do not proceed operation
 */
bool pmw3610_write(uint8_t sensor, uint8_t reg_addr, uint8_t data);

bool           pmw3610_init_wrapper(void);
void           pmw3610_set_cpi_wrapper(uint16_t cpi);
uint16_t       pmw3610_get_cpi_wrapper(void);
report_mouse_t pmw3610_get_report(report_mouse_t mouse_report);
