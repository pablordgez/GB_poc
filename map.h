#ifndef MAP_H
#define MAP_H
#include <stdint.h>
#include <gb/gb.h>
#include "main_definitions.h"
#define TILE_SIZE_BYTES 16
typedef struct {
    uint16_t width;
    uint16_t height;
    const uint8_t* map_data;
} Map;


void init_map(Map* map, uint16_t width, uint16_t height, uint8_t* tiles, uint8_t num_tiles, const uint8_t* map_data);
#endif /* MAP_H */