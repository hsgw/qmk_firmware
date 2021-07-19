/* key matrix size redefine
 * dummy for encoder
 */
#ifdef MATRIX_COLS
#    undef MATRIX_COLS
#    define MATRIX_COLS 15
#endif

/* Key pin assignments redefine
 * unuse D0 pin is dummy
 */

#ifdef DIRECT_PINS
#    undef DIRECT_PINS
#    define DIRECT_PINS                                                    \
        {                                                                  \
            { F5, F4, D3, D2, F6, F7, B1, E6, B3, B2, B6, B5, B4, D0, D0 } \
        }
#endif

#define ENC_KEYMAP_ROW 0
#define ENC_KEYMAP_COL_CW 13
#define ENC_KEYMAP_COL_CCW 14
