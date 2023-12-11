# Copyright (c) 2021 Mike "KemoNine" Crosson
# SPDX-License-Identifier: Apache-2.0

###########
# Fundamental Config
COMBO_ENABLE = yes
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
NKRO_ENABLE = yes
SPACE_CADET_ENABLE = no
TERMINAL_ENABLE = no
VIA_ENABLE = no
WPM_ENABLE = no
ENCODER_ENABLE = no
RGBLIGHT_ENABLE = no

##########
# Combo engine related
VPATH += keyboards/gboards/

###########
# ARDUX Sources
SRC += ardux.c

##########
# Set size for all build steps

ARDUX_SIZE_STD = yes
OPT_DEFS += -DARDUX_SIZE_STD

##########
# User tunable timings
ifndef TAPPING_TERM
	TAPPING_TERM = 175
endif
ifndef COMBO_TERM
	COMBO_TERM = 250
endif
OPT_DEFS += -DTAPPING_TERM=$(TAPPING_TERM) -DCOMBO_TERM=$(COMBO_TERM)


##########
# Set remix for all build steps
ifdef ONESHOT_TAP_TOGGLE
	OPT_DEFS += -DONESHOT_TAP_TOGGLE=$(ONESHOT_TAP_TOGGLE)
else
	OPT_DEFS += -DONESHOT_TAP_TOGGLE=5
endif
ifdef ONESHOT_TIMEOUT
	OPT_DEFS += -DONESHOT_TIMEOUT=$(ONESHOT_TIMEOUT)
else
	OPT_DEFS += -DONESHOT_TIMEOUT=1500
endif
ifdef ARDUX_EXCLAMATION
	OPT_DEFS += -DARDUX_EXCLAMATION=$(ARDUX_EXCLAMATION)
else
	OPT_DEFS += -DARDUX_EXCLAMATION=KC_EXLM
endif

