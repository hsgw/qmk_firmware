#pragma once

// Set matrix dimensions
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

// 74HC138 (Decoder) pins
// Assuming 3 address pins for 8 rows
#define HC138_ADDR_0 GP13
#define HC138_ADDR_1 GP14
#define HC138_ADDR_2 GP15

// 74HC165 (PISO Shift Register) pins
// Assuming two 74HC165 in series for 16 columns
#define HC165_LATCH GP10 // Latch pin (PL)
#define HC165_CLOCK GP9  // Clock pin (CP)
#define HC165_DATA GP11  // Data pin for the 74HC165 chain (QH)
