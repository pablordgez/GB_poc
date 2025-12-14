#include "music_player.h"
uint8_t sound_timer = 0;
const uint16_t note_frequencies[3][7] = {
    // PITCH_LOW (Octave 3)
    {
        1046, // Do (C3) - 130.8 Hz
        1155, // Re (D3) - 146.8 Hz
        1253, // Mi (E3) - 164.8 Hz
        1297, // Fa (F3) - 174.6 Hz
        1379, // Sol (G3) - 196.0 Hz
        1452, // La (A3) - 220.0 Hz
        1517  // Si (B3) - 246.9 Hz
    },
    // PITCH_MEDIUM (Octave 4)
    {
        1547, // Do (C4) - 261.6 Hz
        1602, // Re (D4) - 293.7 Hz
        1650, // Mi (E4) - 329.6 Hz
        1673, // Fa (F4) - 349.2 Hz
        1714, // Sol (G4) - 392.0 Hz
        1750, // La (A4) - 440.0 Hz
        1783  // Si (B4) - 493.9 Hz
    },
    // PITCH_HIGH (Octave 5)
    {
        1798, // Do (C5) - 523.3 Hz
        1825, // Re (D5) - 587.3 Hz
        1850, // Mi (E5) - 659.3 Hz
        1861, // Fa (F5) - 698.5 Hz
        1882, // Sol (G5) - 784.0 Hz
        1900, // La (A5) - 880.0 Hz
        1916  // Si (B5) - 987.8 Hz
    }
};

void music_player_init(void) {
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0x11; 
}


void play_note(Note note, uint16_t duration, Pitch pitch) {
    // Convert duration to number of frames (assuming 60 FPS)
    uint16_t frames = duration / 16;
    if (frames > 255) frames = 255;
    if (frames == 0) frames = 1;

    sound_timer = (uint8_t)frames;

    if (note == NOTE_REST) {
        NR12_REG = 0x00; // 0 volume
        NR14_REG = 0x80; // disable channel
        return;
    }

    if (note > SI || pitch > HIGH) return;

    uint16_t freq = note_frequencies[pitch][note];

    
    NR10_REG = 0x00; // No sweep
    NR11_REG = 0x80; // 50% Duty cycle
    NR12_REG = 0xF0; // Max volume, no volume sweep
    NR13_REG = (uint8_t)(freq & 0xFF);
    NR14_REG = 0x80 | (uint8_t)((freq >> 8) & 0x07);
}

void music_update(void) {
    if (sound_timer > 0) {
        sound_timer--;
        if (sound_timer == 0) {
            NR12_REG = 0x00; // Set volume to 0
            NR14_REG = 0x80; // Disable channel
        }
    }
}