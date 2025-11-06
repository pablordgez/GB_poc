#include "map.h"

void init_map(Map* map, int width, int height, uint8_t* tiles, uint8_t* map_data) {
    map->width = width;
    map->height = height;
    map->map_data = map_data;

    set_bkg_data(0, sizeof(tiles) / sizeof(tiles[0]), tiles);
    set_bkg_tiles(0, 0, width, height, map_data);
}

uint8_t get_map_tile_index(Map* map, int x, int y) {
    return y * map->width + x;
}

void set_map_tile(Map* map, int x, int y, uint8_t tile_index) {
    map->map_data[y * map->width + x] = tile_index;
}