# matrix.c testing options
#  set MATRIX_IO_DELAY macro
#    make MTEST=mdelay0   casasagi:mtei:flash
#    make MTEST=mdelay=1  casasagi:mtei:flash
#    make MTEST=mdelay=10  casasagi:mtei:flash
#  set DEBUG_MATRIX_SCAN_RATE_ENABLE yes
#    make MTEST=scan casasagi:mtei:flash
#  set SERIAL_USART_SPEED
#    make MTEST=serial=500000 casasagi:mtei:flash
#  set MATRIX_COMMON_DELAY -- use quantum/matrix_common.c:matrix_output_unselect_delay()
#    make MTEST=common_delay casasagi:mtei:flash

ifneq ($(strip $(MTEST)),)
  define KEYBOARD_OPTION_PARSE
    # parse 'consle', 'scan', 'no-scan', 'mdelay=?', 'mdelay0',
    #       'common_delay', 'serial=?'
    $(if $(SHOW_PARSE),$(info parse .$1.))  #for debug  'make SHOW_PARSE=y ...'
    ifeq ($(strip $1),console)
        CONSOLE_ENABLE = yes
    endif
    ifeq ($(strip $1),scan)
        DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
    endif
    ifeq ($(strip $1),no-scan)
        DEBUG_MATRIX_SCAN_RATE_ENABLE = no
    endif
    ifneq ($(filter mdelay=%,$1),)
        MDELAY = $(patsubst mdelay=%,%,$1)
    endif
    ifneq ($(filter serial=%,$1),)
        USART_SPEED = $(patsubst serial=%,%,$1)
    endif
    ifeq ($(strip $1),mdelay0)
        MDELAY = 0
    endif
    ifeq ($(strip $1),common_delay)
        MATRIX_COMMON_DELAY = yes
    endif
    ifeq ($(strip $1),no_sync_timer)
	NO_SYNC_TIMER = yes
    endif
    ifeq ($(strip $1),sync_timer)
	NO_SYNC_TIMER = no
    endif
  endef # end of KEYMAP_OPTION_PARSE

  COMMA=,
  $(eval $(foreach A_OPTION_NAME,$(subst $(COMMA), ,$(MTEST)),  \
      $(call KEYBOARD_OPTION_PARSE,$(A_OPTION_NAME))))
endif

ifneq ($(strip $(MDELAY)),)
    OPT_DEFS += -DMATRIX_IO_DELAY=$(strip $(MDELAY))
endif

ifneq ($(strip $(USART_SPEED)),)
    OPT_DEFS += -DSERIAL_USART_SPEED=$(strip $(USART_SPEED))
endif

ifneq ($(strip $(MATRIX_COMMON_DELAY)),yes)
    SRC += own_matrix_delay.c
endif

ifeq ($(strip $(NO_SYNC_TIMER)),yes)
    OPT_DEFS += -DDISABLE_SYNC_TIMER
endif
