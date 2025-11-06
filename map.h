#include <stdint.h>
#include <gb/gb.h>
typedef struct Map{
    int width;
    int height;
    uint8_t* map_data;
} Map;


void init_map(Map* map, int width, int height, uint8_t* tiles, uint8_t* map_data);
uint8_t get_map_tile_index(Map* map, int x, int y);
void set_map_tile(Map* map, int x, int y, uint8_t tile_index);