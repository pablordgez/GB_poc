#ifndef ANIMATION_H
#define ANIMATION_H
#include <stdint.h>
#include <gb/gb.h>
#include <gb/metasprites.h>
#include "main_definitions.h"
#include "actor_declarations.h"

typedef struct {
    uint8_t number_of_frames;
    uint8_t frame_duration;
    uint8_t sprite_id;
    uint8_t sprite_slot;
    uint8_t start_tile;
    uint8_t current_frame;
    uint8_t frame_counter;
    metasprite_t* metasprite;
    uint8_t width;
    uint8_t height;
} Animation;

extern Animation* THIS_ANIMATION;

void sub_init_animation(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t sprite_id);
void init_animation(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t sprite_id);
void init_animation_metasprite(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t sprite_id, uint8_t width, uint8_t height);
void load_animation(Animation* anim, uint8_t x, uint8_t y);
void update_animation(void);
void update_animation_metasprite(uint8_t x, uint8_t y);
void move_animation_sprite(uint8_t x, uint8_t y);
void unload_animation(Animation* anim);
#endif /* ANIMATION_H */