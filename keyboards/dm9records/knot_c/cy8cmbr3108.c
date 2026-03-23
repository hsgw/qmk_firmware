// Copyright 2026 Takuya Urakawa @hsgw (5z6p.ccom)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "cy8cmbr3108.h"
#include "i2c_master.h"
#include "cy8cmbr3108_config.h"
#include "wait.h"
#include "print.h"

// 7-bit I2C address (0x37) shifted for QMK I2C driver
#define I2C_ADDRESS (0x37 << 1)

// CY8CMBR3108 Registers
#define CONFIG_START_REG 0x00
#define CONFIG_CRC_L_REG 0x7E
#define CONFIG_CRC_H_REG 0x7F
#define SENSOR_ID_REG 0x82
#define CTRL_CMD_REG 0x86
#define CTRL_CMD_STATUS_REG 0x88
#define CTRL_CMD_ERR_REG 0x89
#define FAMILY_ID_REG 0x8F
#define DEVICE_ID_REG 0x90
#define BUTTON_STAT_REG 0xAA
#define SYNC_COUNTER1_REG 0xDB
#define DEBUG_SENSOR_ID_REG 0xDC
#define DEBUG_CP_REG 0xDD
#define DEBUG_DIFFERENCE_COUNT0_REG 0xDE
#define DEBUG_BASELINE0_REG 0xE0
#define DEBUG_RAW_COUNT0_REG 0xE2
#define DEBUG_AVG_RAW_COUNT0_REG 0xE4
#define SYNC_COUNTER2_REG 0xE7

// Expected device identifiers
#define EXPECTED_FAMILY_ID 0x9A
#define EXPECTED_DEVICE_ID 0x0A03

// Command codes
#define SAVE_CHECK_CRC 0x02
#define SW_RESET 0xFF

// Retry configuration for reliable communication on wakeup
#define I2C_RETRY_COUNT 3
#define I2C_RETRY_DELAY_MS 340

static bool is_initialized = false;

/**
 * Perform I2C read with retries to handle sensor wakeup delays.
 */
static i2c_status_t i2c_read_reg_retry(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
    i2c_status_t status = I2C_STATUS_ERROR;
    for (int i = 0; i < I2C_RETRY_COUNT; i++) {
        status = i2c_read_register(devaddr, regaddr, data, length, timeout);
        if (status == I2C_STATUS_SUCCESS) return status;
        wait_ms(I2C_RETRY_DELAY_MS);
    }
    return status;
}

/**
 * Perform I2C write with retries.
 */
static i2c_status_t i2c_write_reg_retry(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout) {
    i2c_status_t status = I2C_STATUS_ERROR;
    for (int i = 0; i < I2C_RETRY_COUNT; i++) {
        status = i2c_write_register(devaddr, regaddr, data, length, timeout);
        if (status == I2C_STATUS_SUCCESS) return status;
        wait_ms(I2C_RETRY_DELAY_MS);
    }
    return status;
}

void cy8cmbr3108_init(void) {
    uint8_t data[2];
    uprintf("CY8CMBR3108: Starting init...\n");

    // 1. Verify Family ID
    if (i2c_read_reg_retry(I2C_ADDRESS, FAMILY_ID_REG, data, 1, 100) != I2C_STATUS_SUCCESS || data[0] != EXPECTED_FAMILY_ID) {
        uprintf("CY8CMBR3108: ERR - Family ID mismatch or read failed\n");
        goto fail;
    }

    // 2. Verify Device ID
    if (i2c_read_reg_retry(I2C_ADDRESS, DEVICE_ID_REG, data, 2, 100) != I2C_STATUS_SUCCESS) {
        uprintf("CY8CMBR3108: ERR - Device ID read failed\n");
        goto fail;
    }
    uint16_t device_id = (data[1] << 8) | data[0];
    if (device_id != EXPECTED_DEVICE_ID) {
        uprintf("CY8CMBR3108: ERR - Device ID mismatch (0x%04X)\n", device_id);
        goto fail;
    }
    uprintf("CY8CMBR3108: Hardware ID OK\n");

    // 3. Compare CRC to check if configuration update is needed
    uint8_t crc_data[2];
    bool    needs_update = false;
    if (i2c_read_reg_retry(I2C_ADDRESS, CONFIG_CRC_L_REG, crc_data, 2, 100) == I2C_STATUS_SUCCESS) {
        uint16_t device_crc = (crc_data[1] << 8) | crc_data[0];
        uint16_t config_crc = (CY8CMBR3108_LQXI_configuration[127] << 8) | CY8CMBR3108_LQXI_configuration[126];
        if (device_crc != config_crc) {
            uprintf("CY8CMBR3108: CRC Mismatch (Device: 0x%04X, Config: 0x%04X)\n", device_crc, config_crc);
            needs_update = true;
        }
    } else {
        uprintf("CY8CMBR3108: ERR - CRC read failed\n");
        goto fail;
    }

    // 4. Update and save configuration if there's a mismatch
    if (needs_update) {
        uprintf("CY8CMBR3108: Updating configuration...\n");
        if (i2c_write_reg_retry(I2C_ADDRESS, CONFIG_START_REG, CY8CMBR3108_LQXI_configuration, 128, 500) != I2C_STATUS_SUCCESS) {
            uprintf("CY8CMBR3108: ERR - Configuration RAM write failed\n");
            goto fail;
        }

        uint8_t save_cmd = SAVE_CHECK_CRC;
        i2c_write_reg_retry(I2C_ADDRESS, CTRL_CMD_REG, &save_cmd, 1, 100);
        wait_ms(220); // Required wait for flash write

        if (i2c_read_reg_retry(I2C_ADDRESS, CTRL_CMD_STATUS_REG, data, 1, 100) != I2C_STATUS_SUCCESS || data[0] != 0) {
            uprintf("CY8CMBR3108: ERR - Configuration save to flash failed (Status: %d)\n", data[0]);
            goto fail;
        }
        uprintf("CY8CMBR3108: Configuration Updated Successfully\n");
    } else {
        uprintf("CY8CMBR3108: Configuration OK\n");
    }

    // 5. Software reset to apply changes and start sensing
    uint8_t reset_cmd = SW_RESET;
    if (i2c_write_reg_retry(I2C_ADDRESS, CTRL_CMD_REG, &reset_cmd, 1, 100) != I2C_STATUS_SUCCESS) {
        uprintf("CY8CMBR3108: ERR - Reset command failed\n");
        goto fail;
    }
    wait_ms(30);

    is_initialized = true;
    uprintf("CY8CMBR3108: Initialization Success\n");
    return;

fail:
    uprintf("CY8CMBR3108: Initialization Failed\n");
}

uint16_t cy8cmbr3108_read(void) {
    if (!is_initialized) return 0;

    uint8_t stat_data[2];
    if (i2c_read_register(I2C_ADDRESS, BUTTON_STAT_REG, stat_data, 2, 100) == I2C_STATUS_SUCCESS) {
        return (stat_data[1] << 8) | stat_data[0];
    }
    return 0;
}

bool cy8cmbr3108_is_ready(void) {
    return is_initialized;
}
