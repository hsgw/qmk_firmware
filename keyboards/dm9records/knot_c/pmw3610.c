// This code is based on https://github.com/inorichi/zmk-pmw3610-driver
#include "pointing_device_internal.h"
#include "pmw3610.h"
#include "string.h"
#include "wait.h"
#include "progmem.h"

// 12-bit two's complement value to int16_t
// adapted from https://stackoverflow.com/questions/70802306/convert-a-12-bit-signed-number-in-c
#define TOINT16(val, bits) (((struct { int16_t value : bits; }){val}).value)
#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

const pointing_device_driver_t pmw3610_pointing_device_driver = {
    .init       = pmw3610_init_wrapper,
    .get_report = pmw3610_get_report,
    .set_cpi    = pmw3610_set_cpi_wrapper,
    .get_cpi    = pmw3610_get_cpi_wrapper,
};

bool pmw3610_spi_start(uint8_t sensor) {
    // TODO: only one sensor is supported
    if (cs_pin != NO_PIN) {
        gpio_write_pin_low(cs_pin);
    }
    wait_us(1);
    return true;
}

bool pmw3610_spi_stop(uint8_t sensor) {
    // TODO: only one sensor is supported
    if (cs_pin != NO_PIN) {
        gpio_write_pin_high(cs_pin);
    }
    return true;
}

bool _pmw3610_write(uint8_t sensor, uint8_t reg_addr, uint8_t data) {
    reg_addr |= PMW3610_SPI_WRITE_BIT;
    if (!pmw3610_spi_start(sensor)) {
        return false;
    }
    gpio_set_pin_output(sdio_pin);
    for (int8_t i = 7; i >= 0; i--) {
        gpio_write_pin_low(sclk_pin);
        gpio_write_pin(sdio_pin, reg_addr & (1 << i));
        wait_us(PMW3610_T_NCS_SCLK);
        gpio_write_pin_high(sclk_pin);
        wait_us(PMW3610_T_NCS_SCLK);
    }
    for (int8_t i = 7; i >= 0; i--) {
        gpio_write_pin_low(sclk_pin);
        gpio_write_pin(sdio_pin, data & (1 << i));
        wait_us(PMW3610_T_NCS_SCLK);
        gpio_write_pin_high(sclk_pin);
        wait_us(PMW3610_T_NCS_SCLK);
    }
    wait_us(PMW3610_T_SCLK_NCS_WR);
    pmw3610_spi_stop(sensor);

    wait_us(PMW3610_T_SWX);
    return true;
}

bool pmw3610_write(uint8_t sensor, uint8_t reg_addr, uint8_t data) {
    if (!_pmw3610_write(sensor, PMW3610_REG_SPI_CLK_ON_REQ, PMW3610_SPI_CLOCK_CMD_ENABLE)) {
        return false;
    }
    if (!_pmw3610_write(sensor, reg_addr, data)) {
        return false;
    }
    if (!_pmw3610_write(sensor, PMW3610_REG_SPI_CLK_ON_REQ, PMW3610_SPI_CLOCK_CMD_DISABLE)) {
        return false;
    }
    return true;
}

uint8_t pmw3610_read(uint8_t sensor, uint8_t reg_addr) {
    if (!pmw3610_spi_start(sensor)) {
        return 0;
    }
    gpio_set_pin_output(sdio_pin);
    for (int8_t i = 7; i >= 0; i--) {
        gpio_write_pin_low(sclk_pin);
        gpio_write_pin(sdio_pin, reg_addr & (1 << i));
        wait_us(PMW3610_T_NCS_SCLK);
        gpio_write_pin_high(sclk_pin);
        wait_us(PMW3610_T_NCS_SCLK);
    }
    gpio_set_pin_input(sdio_pin);
    wait_us(PMW3610_T_SRAD);
    uint8_t data = 0;
    for (int8_t i = 7; i >= 0; i--) {
        gpio_write_pin_low(sclk_pin);
        wait_us(PMW3610_T_SRX);
        gpio_write_pin_high(sclk_pin);
        wait_us(PMW3610_T_SRX);
        data |= gpio_read_pin(sdio_pin) << i;
    }
    wait_us(PMW3610_T_NCS_SCLK);
    pmw3610_spi_stop(sensor);

    wait_us(PMW3610_T_SRX);
    return data;
}

bool set_downshift_time(uint8_t sensor, uint8_t reg_addr, uint32_t time) {
    uint32_t maxtime;
    uint32_t mintime;

    switch (reg_addr) {
        case PMW3610_REG_RUN_DOWNSHIFT:
            /*
             * Run downshift time = PMW3610_REG_RUN_DOWNSHIFT
             *                      * 8 * pos-rate (fixed to 4ms)
             */
            maxtime = 32 * 255;
            mintime = 32; // hard-coded in pmw3610_async_init_configure
            break;

        case PMW3610_REG_REST1_DOWNSHIFT:
            /*
             * Rest1 downshift time = PMW3610_REG_RUN_DOWNSHIFT
             *                        * 16 * Rest1_sample_period (default 40 ms)
             */
            maxtime = 255 * 16 * PMW3610_REST1_SAMPLE_TIME_MS;
            mintime = 16 * PMW3610_REST1_SAMPLE_TIME_MS;
            break;

        case PMW3610_REG_REST2_DOWNSHIFT:
            /*
             * Rest2 downshift time = PMW3610_REG_REST2_DOWNSHIFT
             *                        * 128 * Rest2 rate (default 100 ms)
             */
            maxtime = 255 * 128 * PMW3610_REST2_SAMPLE_TIME_MS;
            mintime = 128 * PMW3610_REST2_SAMPLE_TIME_MS;
            break;
        default:
            pd_dprintf("PMW33XX (%d): set_downshift_time: not supported adder %d\n", sensor, reg_addr);
            return false;
    }

    if ((time > maxtime) || (time < mintime)) {
        pd_dprintf("PMW33XX (%d): set_downshift_time: out of range %lu\n", sensor, time);
        return false;
    }

    /* Convert time to register value */
    uint8_t value = time / mintime;

    if (!pmw3610_write(sensor, reg_addr, value)) {
        pd_dprintf("PMW33XX (%d): set_downshift_time: failed to write %d\n", sensor, value);
        return false;
    }
    return true;
}

bool set_sample_time(uint8_t sensor, uint8_t reg_addr, uint32_t sample_time) {
    uint32_t maxtime = 2550;
    uint32_t mintime = 10;
    if ((sample_time > maxtime) || (sample_time < mintime)) {
        pd_dprintf("PMW33XX (%d): set_sample_time: out of range %lu\n", sensor, sample_time);
        return false;
    }

    uint8_t value = sample_time / mintime;

    /* The sample time is (reg_value * mintime ) ms. 0x00 is rounded to 0x1 */
    if (pmw3610_write(sensor, reg_addr, value)) {
        pd_dprintf("PMW33XX (%d): set_sample_time: failed to write %d\n", sensor, value);
        return false;
    }
    return true;
}
void pmw3610_set_cpi(uint8_t sensor, uint16_t cpi) {
    /* Set resolution with CPI step of 200 cpi
     * 0x1: 200 cpi (minimum cpi)
     * 0x2: 400 cpi
     * 0x3: 600 cpi
     * :
     */

    if ((cpi > PMW3610_MAX_CPI) || (cpi < PMW3610_MIN_CPI)) {
        pd_dprintf("PMW33XX (%d): set_cpi: out of range %u\n", sensor, cpi);
        return;
    }

    // Convert CPI to register value
    uint8_t value = (cpi / 200);

    /* set the cpi */
    pmw3610_write(sensor, PMW3610_REG_SPI_PAGE0, 0xFF);
    pmw3610_write(sensor, PMW3610_REG_RES_STEP, value);
    pmw3610_write(sensor, PMW3610_REG_SPI_PAGE1, 0x00);
    return;
}

bool pmw3610_init(uint8_t sensor) {
    // set by common code
    // gpio_set_pin_input(motion_pin);
    gpio_set_pin_output(sclk_pin);
    gpio_set_pin_output(sdio_pin);
    if (cs_pin != NO_PIN) {
        gpio_set_pin_output(cs_pin);
    }

    wait_ms(10);
    if (!pmw3610_write(sensor, PMW3610_REG_POWER_UP_RESET, PMW3610_POWERUP_CMD_RESET)) {
        return false;
    }
    wait_ms(200);
    if (!pmw3610_write(sensor, PMW3610_REG_OBSERVATION, 0x00)) {
        return false;
    }
    wait_ms(100);
    uint8_t obs = pmw3610_read(sensor, PMW3610_REG_OBSERVATION);
    if ((obs & 0x0F) != 0x0F) {
        pd_dprintf("PMW3610 (%d): unexpected observation: %d\n", sensor, obs);
        return false;
    }
    uint8_t product_id = pmw3610_read(sensor, PMW3610_REG_PRODUCT_ID);
    if (product_id != PMW3610_PRODUCT_ID) {
        pd_dprintf("PMW3610 (%d): unexpected product id: %d\n", sensor, product_id);
        return false;
    }
    pmw3610_read(sensor, PMW3610_REG_MOTION);
    pmw3610_read(sensor, PMW3610_REG_DELTA_X_L);
    pmw3610_read(sensor, PMW3610_REG_DELTA_Y_L);
    pmw3610_read(sensor, PMW3610_REG_DELTA_XY_H);

    pmw3610_set_cpi(sensor, PMW3610_CPI);
    pmw3610_write(sensor, PMW3610_REG_PERFORMANCE, PMW3610_PERFORMANCE_VALUE);
    set_downshift_time(sensor, PMW3610_REG_RUN_DOWNSHIFT, 128);
    set_downshift_time(sensor, PMW3610_REG_REST1_PERIOD, 40);
    set_downshift_time(sensor, PMW3610_REG_REST1_DOWNSHIFT, 9600);
    // set_downshift_time(sensor, PMW3610_REG_REST2_DOWNSHIFT, TODO);
    // set_sample_time(sensor, PMW3610_REG_REST2_PERIOD, TODO);
    // set_sample_time(sensor, PMW3610_REG_REST3_PERIOD, TODO);
    return true;
}

uint16_t pmw3610_get_cpi(uint8_t sensor) {
    pmw3610_write(sensor, PMW3610_REG_SPI_PAGE0, 0xFF);
    uint8_t cpival = pmw3610_read(sensor, PMW3610_REG_RES_STEP);
    pmw3610_write(sensor, PMW3610_REG_SPI_PAGE1, 0x00);
    return (uint16_t)((cpival + 1) & 0xFF) * PMW3610_CPI_STEP;
}

bool pmw3610_init_wrapper(void) {
    return pmw3610_init(0);
}

void pmw3610_set_cpi_wrapper(uint16_t cpi) {
    pmw3610_set_cpi(0, cpi);
}

uint16_t pmw3610_get_cpi_wrapper(void) {
    return pmw3610_get_cpi(0);
}

report_mouse_t pmw3610_get_report(report_mouse_t mouse_report) {
    static bool in_motion = false;
    uint8_t     motion    = pmw3610_read(0, PMW3610_REG_MOTION);
    if (!(motion & PMW3610_MOTION_BIT)) {
        in_motion = false;
        return mouse_report;
    }
    if (!in_motion) {
        in_motion = true;
    }
    uint8_t xl  = pmw3610_read(0, PMW3610_REG_DELTA_X_L);
    uint8_t yl  = pmw3610_read(0, PMW3610_REG_DELTA_Y_L);
    uint8_t xyh = pmw3610_read(0, PMW3610_REG_DELTA_XY_H);

    int16_t dx = TOINT16((xl | ((xyh & 0xF0) << 4)), 12);
    int16_t dy = TOINT16((yl | ((xyh & 0x0F) << 8)), 12);

    mouse_report.x = CONSTRAIN_HID_XY(dx);
    mouse_report.y = CONSTRAIN_HID_XY(dy);
    return mouse_report;
}

bool pointing_device_driver_init(void) {
    return pmw3610_init(0);
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    return pmw3610_get_report(mouse_report);
}

uint16_t pointing_device_driver_get_cpi(void) {
    return pmw3610_get_cpi(0);
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
    pmw3610_set_cpi(0, cpi);
}
