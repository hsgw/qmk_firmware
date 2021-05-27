/*
 * File: adaptive_matrix_delay.c
 *
 *   Replace 'matrix_output_unselect_delay()' with the process of monitoring until Col lines returns to High.
 *
 *   You need to define the MATRIX_IO_DELAY_PORTS and MATRIX_IO_DELAY_MASKS macros in config.h.
 *   e.g.
 *    #define MATRIX_COL_PINS { B2, B1, B0, A7, C13, B9, B8 }
 *    #define MATRIX_IO_DELAY_PORTS A0, B0, C0
 *    //                              fedcba9876543210    fedcba9876543210    fedcba9876543210
 *    #define MATRIX_IO_DELAY_MASKS 0b0000000010000000, 0b0000001100000111, 0b0010000000000000
 *
 *   Then add the following line in rules.mk:
 *     SRC += adaptive_matrix_delay.c
 */
#include "quantum.h"

#ifdef MATRIX_DEBUG_PIN
#  define DEBUG_PIN_INIT()  setPinOutput(MATRIX_DEBUG_PIN);  writePinLow(MATRIX_DEBUG_PIN)
#  define DEBUG_PIN_ON()    writePinHigh(MATRIX_DEBUG_PIN)
#  define DEBUG_PIN_OFF()   writePinLow(MATRIX_DEBUG_PIN)
#else
#  define DEBUG_PIN_INIT()
#  define DEBUG_PIN_ON()
#  define DEBUG_PIN_OFF()
#endif

#ifndef readPort
#    if defined(__AVR__)
#        define readPort(pin) PINx_ADDRESS(pin)
         typedef uint8_t     port_data_t;
#    else
#        define readPort(pin) palReadPort(PAL_PORT(pin))
         typedef uint16_t    port_data_t;
#    endif
#endif

static const pin_t delay_ports[] = { MATRIX_IO_DELAY_PORTS };
static const port_data_t delay_masks[] = { MATRIX_IO_DELAY_MASKS };
#ifdef MATRIX_IO_DELAY_PORTS_RIGHT
static const pin_t delay_ports_right[] = { MATRIX_IO_DELAY_PORTS_RIGHT };
static const port_data_t delay_masks_right[] = { MATRIX_IO_DELAY_MASKS_RIGHT };
#endif

#ifdef MATRIX_DEBUG_PIN
void keyboard_post_init_user(void) {
    DEBUG_PIN_INIT();
}
#endif

void matrix_output_unselect_delay(void) {
    bool is_pressed;
    const pin_t *ports = delay_ports;
    const port_data_t *masks = delay_masks;
    uint8_t num_ports = sizeof(delay_ports)/sizeof(pin_t);
#ifdef MATRIX_IO_DELAY_PORTS_RIGHT
    if (!is_keyboard_left()) {
        ports = delay_ports_right;
        masks = delay_masks_right;
        num_ports = sizeof(delay_ports_right)/sizeof(pin_t);
    }
#endif
    DEBUG_PIN_ON();
    do {
        is_pressed = false;
        for (uint8_t i = 0; i < num_ports; i++ ) {
            is_pressed |= ( (readPort(ports[i]) & masks[i]) != masks[i] );
        }
    } while (is_pressed);
    DEBUG_PIN_OFF();
}
