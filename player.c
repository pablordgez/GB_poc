#include <gb/gb.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"


void init_player(struct player* p, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t sprite_id, uint8_t first_tile, uint8_t num_sprites, uint8_t frames_per_sprite, SpriteManager* sprite_manager) {
    p->x = x;
    p->y = y;
    p->width = width;
    p->height = height;
    p->drawX = x >> 4;
    p->drawY = y >> 4;
    p->sprite_id = sprite_id;
    p->first_tile = first_tile;
    p->num_sprites = num_sprites;
    p->frames_per_sprite = frames_per_sprite;
    p->current_sprite = first_tile;
    p->current_frame = 0;

    if(!is_sprite_manager_initialized(sprite_manager)) {
        return; // Sprite manager not initialized
    }
    SpriteEntry* sprites = get_sprites(sprite_manager, sprite_id, num_sprites);
    if(sprites != (void*)0) {
        for(uint8_t i = 0; i < num_sprites; i++) {
            set_sprite_data(first_tile + i * (width * height), width * height, sprites[i].data);
        }
        if(width > 1 || height > 1) {
            init_metasprite(p);
        } else{
            set_sprite_tile(sprite_id, first_tile);
            move_sprite(0, p->drawX, p->drawY);
        }
        SHOW_SPRITES;
    }
    
    free(sprites);
}

void init_metasprite(struct player* p) {
    metasprite_t* player_metasprite = malloc(sizeof(metasprite_t) * (p->width * p->height + 1));
    if(player_metasprite == (void*)0) {
        return; // Memory allocation failed
    }
    int8_t pivotY = -8 * (p->height / 2);
    int8_t pivotX = -8 * (p->width / 2);
    for(uint8_t i = 0; i < p->height; i++){
        for(uint8_t j = 0; j < p->width; j++){
            player_metasprite[i * p->width + j].dy = pivotY;
            player_metasprite[i * p->width + j].dx = pivotX;
            pivotY = 0;
            pivotX = 8;
            player_metasprite[i * p->width + j].dtile = p->first_tile + (i * p->width + j);
            player_metasprite[i * p->width + j].props = 0;
        }
        pivotY = 8;
        pivotX = -8 * (p->width / 2);
    }
    player_metasprite[p->width * p->height].dy = metasprite_end;
    player_metasprite[p->width * p->height].dx = 0;
    player_metasprite[p->width * p->height].dtile = 0;
    player_metasprite[p->width * p->height].props = 0;
    p->metasprite = player_metasprite;
    move_metasprite_ex(player_metasprite, p->first_tile, 0, p->sprite_id, p->drawX, p->drawY);
}


void move_player(struct player* p, int8_t dx, int8_t dy) {
    p->x += dx;
    p->y += dy;
    p->drawX = p->x >> 4;
    p->drawY = p->y >> 4;
    if(p->metasprite != (void*)0) {
        move_metasprite_ex(p->metasprite, p->first_tile + p->current_sprite * p->width * p->height, 0, p->sprite_id, p->drawX, p->drawY);
    }
    else{
        move_sprite(0, p->drawX, p->drawY);
    }
}

void update_player(struct player* p) {
    p->current_frame++;
    if(p->current_frame < p->frames_per_sprite) {
        return;
    }
    p->current_frame = 0;
    if(p->current_sprite >= p->num_sprites - 1) {
        p->current_sprite = 0;
    } else {
        p->current_sprite++;
    }
    if(p->metasprite != (void*)0) {
        move_metasprite_ex(p->metasprite, p->first_tile + p->current_sprite * p->width * p->height, 0, p->sprite_id, p->drawX, p->drawY);
    } else{
        set_sprite_tile(p->sprite_id, p->first_tile + p->current_sprite);
    }
    
}