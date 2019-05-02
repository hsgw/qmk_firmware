#pragma once

#define PROGRAM_DIR tetris

#define EDITOR_OPEN()    SEND_STRING("vim tetris/")
#define EDITOR_INPUT()   SEND_STRING("i")
#define EDITOR_CLOSE()   tap_code(KC_ESC);SEND_STRING(":wq"SS_TAP(X_ENTER))

#define MAKE_DIR()       SEND_STRING("mkdir tetris"SS_TAP(X_ENTER))
#define REMOVE_DIR()     SEND_STRING("rm -r tetris"SS_TAP(X_ENTER))
