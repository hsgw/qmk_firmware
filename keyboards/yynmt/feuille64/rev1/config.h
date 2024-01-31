/*
Copyright 2021 yynmt

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Encoder */
#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A \
        { D2, D3, D1 }
#    define ENCODERS_PAD_B \
        { D1, D2, D3 }
#    define ENCODER_RESOLUTION 4
#    define TAP_CODE_DELAY 10
#endif

/* MIDI */
#ifdef MIDI_ENABLE
#    define MIDI_ADVANCED
#endif

#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 9
