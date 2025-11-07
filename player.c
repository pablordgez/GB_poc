#include <gb/gb.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"


void init_player(Player* p, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t sprite_id, uint8_t first_tile, uint8_t num_sprites, uint8_t frames_per_sprite, SpaceManager* sprite_manager) {
    init_actor(&p->base, x, y, width, height, sprite_id, first_tile, num_sprites, frames_per_sprite, sprite_manager);
}

void init_metasprite_player(Player* p) {
    init_metasprite(&p->base);
}

void move_player(Player* p, int8_t dx, int8_t dy) {
    move_actor(&p->base, dx, dy);
}

void update_player_frame(Player* p) {
    update_actor_frame(&p->base);
}