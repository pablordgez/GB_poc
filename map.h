#ifndef MAP_H
#define MAP_H
#include <stdint.h>
#include <gb/gb.h>
#include "main_definitions.h"
#include "asset_manager.h"
#define TILE_SIZE_BYTES 16
typedef struct {
    uint8_t id;
    uint16_t width;
    uint16_t height;
    const uint8_t* map_data;
} Map;


void init_map(Map* map, uint16_t width, uint16_t height, const uint8_t* map_data, uint8_t id);
void load_map(Map* map, uint8_t* tiles, uint8_t num_tiles);
#endif /* MAP_H */