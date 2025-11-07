#include "actor.h"
#include <stdio.h>

void init_actor(Actor* actor, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t sprite_id, uint8_t first_tile, uint8_t num_sprites, uint8_t frames_per_sprite, SpaceManager* sprite_manager) {
    actor->x = x;
    actor->y = y;
    actor->width = width;
    actor->height = height;
    actor->drawX = (x >> 4) + 8;
    actor->drawY = (y >> 4) + 16;
    actor->sprite_id = sprite_id;
    actor->first_tile = first_tile;
    actor->num_sprites = num_sprites;
    actor->frames_per_sprite = frames_per_sprite;
    actor->current_sprite = 0;
    actor->current_frame = 0;

    for(uint8_t i = 0; i < num_sprites; i++) {
        const SpaceEntry* sprite_data = get_space_entry(sprite_manager, sprite_id, i);
        if(sprite_data != (void*)0) {
            uint8_t prev_bank = _current_bank;
            SWITCH_ROM(sprite_data->bank);
            set_sprite_data(first_tile + i * (width * height), width * height, sprite_data->data);
            SWITCH_ROM(prev_bank);
        }
    }
    if(width > 1 || height > 1) {
        init_metasprite(actor);
    } else {
        set_sprite_tile(sprite_id, first_tile);
        move_sprite(sprite_id, actor->drawX, actor->drawY);
        actor->metasprite = (void*)0;
    }
}

void init_metasprite(Actor* actor) {
    metasprite_t* actor_metasprite = malloc(sizeof(metasprite_t) * (actor->width * actor->height + 1));
    if(actor_metasprite == (void*)0) {
        return; // Memory allocation failed
    }
    int8_t pivotY = -8 * (actor->height / 2);
    int8_t pivotX = -8 * (actor->width / 2);
    for(uint8_t i = 0; i < actor->height; i++){
        for(uint8_t j = 0; j < actor->width; j++){
            actor_metasprite[i * actor->width + j].dy = pivotY;
            actor_metasprite[i * actor->width + j].dx = pivotX;
            pivotY = 0;
            pivotX = 8;
            actor_metasprite[i * actor->width + j].dtile = actor->first_tile + (i * actor->width + j);
            actor_metasprite[i * actor->width + j].props = 0;
        }
        pivotY = 8;
        pivotX = -8 * (actor->width / 2);
    }
    actor_metasprite[actor->width * actor->height].dy = metasprite_end;
    actor_metasprite[actor->width * actor->height].dx = 0;
    actor_metasprite[actor->width * actor->height].dtile = 0;
    actor_metasprite[actor->width * actor->height].props = 0;
    actor->metasprite = actor_metasprite;
    move_metasprite_ex(actor_metasprite, actor->first_tile, 0, actor->sprite_id, actor->drawX, actor->drawY);
}


void move_actor(Actor* actor, int8_t dx, int8_t dy) {
    actor->x += dx;
    actor->y += dy;
    actor->drawX = (actor->x >> 4) + 8;
    actor->drawY = (actor->y >> 4) + 16;
    if(actor->metasprite != (void*)0) {
        move_metasprite_ex(actor->metasprite, actor->first_tile + actor->current_sprite * actor->width * actor->height, 0, actor->sprite_id, actor->drawX, actor->drawY);
    }
    else{
        move_sprite(0, actor->drawX, actor->drawY);
    }
}

void update_actor_frame(Actor* actor) {
    actor->current_frame++;
    if(actor->current_frame < actor->frames_per_sprite) {
        return;
    }
    actor->current_frame = 0;
    if(actor->current_sprite >= actor->num_sprites - 1) {
        actor->current_sprite = 0;
    } else {
        actor->current_sprite++;
    }
    if(actor->metasprite != (void*)0) {
        move_metasprite_ex(actor->metasprite, actor->first_tile + actor->current_sprite * actor->width * actor->height, 0, actor->sprite_id, actor->drawX, actor->drawY);
    } else{
        set_sprite_tile(actor->sprite_id, actor->first_tile + actor->current_sprite);
    }
    
}