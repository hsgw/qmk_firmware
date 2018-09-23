#include <LUFA/Drivers/USB/USB.h>
#include "midi.h"
#include "qmk_midi.h"

extern MidiDevice midi_device;

void my_sysex_callback(MidiDevice * device, uint16_t start, uint8_t length, uint8_t * data);

void midi_register_callbacks(void);
