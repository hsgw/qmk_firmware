#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 300
#define PERMISSIVE_HOLD

#define RGBLIGHT_LIMIT_VAL 180

#define MATRIX_IO_DELAY_PORTS B0
//                              fedcba9876543210
#define MATRIX_IO_DELAY_MASKS 0b0000000100111111

#define MATRIX_IO_DELAY_PORTS_RIGHT A0, B0, C0
//                                    fedcba9876543210    fedcba9876543210    fedcba9876543210
#define MATRIX_IO_DELAY_MASKS_RIGHT 0b0000000010000000, 0b0000001100000111, 0b0010000000000000
