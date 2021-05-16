#include <stdint.h>
#include "quantum.h"
#include "wait.h"

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

#ifdef ACCURATE_DELAY
static void half_micro_delay(void) {
    wait_cpuclock(STM32_SYSCLK / 1000000L / 2);
}

static void wait_accurate_us(unsigned int n) {
    for (n *= 2; n > 0; n--) {
        half_micro_delay();
    }
}
#undef wait_us
#define wait_us(n) wait_accurate_us(n)
#endif

/* In tmk_core/common/wait.h, the implementation for PROTOCOL_CHIBIOS
 * calls 'chThdSleepMicroseconds(1)' when 'wait_us(0)'.
 * However, 'wait_us(0)' should do nothing. */
void matrix_output_unselect_delay(void) {
    if (MATRIX_IO_DELAY > 0) {
        wait_us(MATRIX_IO_DELAY);
    }
}
