#include <stdint.h>
#include <gb/metasprites.h>
#include <gb/gb.h>
#include <stdlib.h>
#include "sprite_manager.h"
typedef struct{
    uint16_t x;
    uint16_t y;
    uint8_t width;
    uint8_t height;
    uint8_t drawX;
    uint8_t drawY;
    uint8_t sprite_id;
    uint8_t first_tile;
    uint8_t num_sprites;
    uint8_t current_sprite;
    uint8_t frames_per_sprite;
    uint8_t current_frame;
    metasprite_t* metasprite;
} Actor;

void init_actor(Actor* actor, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t sprite_id, uint8_t first_tile, uint8_t num_sprites, uint8_t frames_per_sprite, SpriteManager* sprite_manager);
void init_metasprite(Actor* actor);
void move_actor(Actor* actor, int8_t dx, int8_t dy);
void update_actor(Actor* actor);