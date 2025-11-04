#include "sprite_manager.h"
#include <stdlib.h>

void init_sprite_manager(SpriteManager* manager, uint8_t max_count) {
    manager->entries = (SpriteEntry*)malloc(max_count * sizeof(SpriteEntry));
    if(!manager->entries) {
        manager->count = 0;
        manager->max_count = 0;
        return; // Memory allocation failed
    }
    manager->count = 0;
    manager->max_count = max_count;
}

SpriteEntry* get_sprite(SpriteManager* manager, uint8_t id) {
    for (uint8_t i = 0; i < manager->count; i++) {
        if (manager->entries[i].id == id) {
            return &manager->entries[i];
        }
    }
    return (void*)0; // Sprite not found
}

void add_sprite(SpriteManager* manager, SpriteEntry entry) {
    if(manager->count >= manager->max_count) {
        return; // Cannot add more sprites
    }
    manager->entries[manager->count] = entry;
    manager->count++;
}

void free_sprite_manager(SpriteManager* manager) {
    free(manager->entries);
    manager->entries = (void*)0;
    manager->count = 0;
    manager->max_count = 0;
}

int is_sprite_manager_initialized(SpriteManager* manager) {
    return manager->entries != (void*)0;
}


SpriteEntry* get_sprites(SpriteManager* manager, uint8_t start_id, uint8_t num_sprites) {
    if(start_id + num_sprites > manager->count) {
        return (void*)0; // Out of bounds
    }
    SpriteEntry* sprites = malloc(sizeof(SpriteEntry*) * num_sprites);
    if(!sprites) {
        return (void*)0; // Memory allocation failed
    }
    for(uint8_t i = 0; i < num_sprites; i++) {
        sprites[i] = *get_sprite(manager, start_id + i);
    }
    return sprites;
}