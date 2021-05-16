#include "quantum.h"
#include "wait.h"

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

/* In tmk_core/common/wait.h, the implementation for PROTOCOL_CHIBIOS
 * calls 'chThdSleepMicroseconds(1)' when 'wait_us(0)'.
 * However, 'wait_us(0)' should do nothing. */
void matrix_output_unselect_delay(void) {
    if (MATRIX_IO_DELAY > 0) {
        wait_us(MATRIX_IO_DELAY);
    }
}
