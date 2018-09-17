#include "midi_callbacks.h"

#include "print.h"

#define SYSEX_BUFFER_LENGTH 64

uint8_t sysex_buffer[SYSEX_BUFFER_LENGTH] = {0};

void my_sysex_callback(MidiDevice * device, uint16_t start, uint8_t length, uint8_t * data) {

  uint8_t sysex_pos;

  if (start == 0) {
    sysex_pos = 0;
    data++;
    length--;
  } else {
    sysex_pos = start - 1;
  }

  for (int i=0;i<length;i++) {
    if (*data == 0xF7) {
      print("sysex ");
      for(int j=0;j<sysex_pos;j++){
        printf("%d ", sysex_buffer[j]);
      }
      print("\n");
      sysex_pos = 0;
      return;
    } else if (sysex_pos >= SYSEX_BUFFER_LENGTH) {
      print("sysex buffer over run\n");
      return;
    }

    sysex_buffer[sysex_pos] = *data;
    data++;
    sysex_pos++;
  }
}

// void my_fallthrough_callback(MidiDevice * device,
//     uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2){

//   if (cnt == 3) {
//     switch (byte0 & 0xF0) {
//         case MIDI_NOTEON:
//             print("note on\n");
//             break;
//         case MIDI_NOTEOFF:
//             print("note off\n");
//             break;
//     }
//   }
// }

void midi_register_callbacks(void) {
  midi_register_sysex_callback(&midi_device, my_sysex_callback);
  // midi_register_fallthrough_callback(&midi_device, my_fallthrough_callback);
}
