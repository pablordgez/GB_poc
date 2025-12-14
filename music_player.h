#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H
#include <stdint.h>
#include "gb/gb.h"

typedef enum {
    DO,
    RE,
    MI,
    FA,
    SOL,
    LA,
    SI,
    NOTE_REST
} Note;

typedef enum {
    LOW,
    MEDIUM,
    HIGH
} Pitch;

void music_player_init(void);
void play_note(Note note, uint16_t duration_ms, Pitch pitch);
void music_update(void);
#endif // MUSIC_PLAYER_H