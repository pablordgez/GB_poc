#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <stdint.h>
#include <gb/gb.h>

typedef struct{
    uint8_t id;
    uint8_t* data;
} SpriteEntry;

typedef struct{
    SpriteEntry* entries;
    uint8_t count;
    uint8_t max_count;
} SpriteManager;


void init_sprite_manager(SpriteManager* manager, uint8_t max_count);
SpriteEntry* get_sprite(SpriteManager* manager, uint8_t id);
SpriteEntry* get_sprites(SpriteManager* manager, uint8_t start_id, uint8_t num_sprites);
void add_sprite(SpriteManager* manager, SpriteEntry entry);
void free_sprite_manager(SpriteManager* manager);
int is_sprite_manager_initialized(SpriteManager* manager);
#endif