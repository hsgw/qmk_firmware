#!/bin/bash

make V=1 -r -R -C ./ -f build_keyboard.mk  KEYBOARD=${1} KEYMAP=${2} SILENT=false ${3}

exit 0
