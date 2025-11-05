#include "tile_manager.h"

void init_tile_manager(TileManager* manager, uint8_t total_tiles) {
    manager->total_tiles = total_tiles;
    manager->registered_tiles = malloc(total_tiles * sizeof(TileEntry));
    if(!manager->registered_tiles) {
        manager->total_tiles = 0;
        manager->registered_count = 0;
        return; // Memory allocation failed
    }
    manager->registered_count = 0;
}

void register_tiles(TileManager* manager, TileEntry tiles) {
    if(manager->registered_count + tiles.size > manager->total_tiles) {
        return; // Not enough space to register new tiles
    }
    manager->registered_tiles[manager->registered_count] = tiles;
    manager->registered_count += 1;
}

uint8_t get_free_tiles_position(TileManager* manager, uint8_t size){
    for(uint8_t i = 0; i <= manager->total_tiles - size; i++) {
        uint8_t found = 1;
        for(uint8_t j = 0; j < manager->registered_count; j++) {
            TileEntry entry = manager->registered_tiles[j];
            if((i >= entry.position && i < entry.position + entry.size) || (i + size > entry.position && i + size <= entry.position + entry.size)) {
                found = 0;
                break;
            }
        }
        if(found) {
            return i;
        }
    }
    return 0;
}

void free_tile_manager(TileManager* manager) {
    free(manager->registered_tiles);
    manager->registered_tiles = (void*)0;
    manager->total_tiles = 0;
    manager->registered_count = 0;
    free(manager);
}