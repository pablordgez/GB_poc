#include "map.h"

void init_map(Map* map, uint16_t width, uint16_t height, 
              const uint8_t* tiles, uint8_t num_tiles, const uint8_t* map_data) {
    
    map->width = width;
    map->height = height;
    map->map_data = map_data;

    if (num_tiles > 0) {
        set_bkg_data(0, num_tiles, tiles);
    }


    uint8_t draw_w = SCREEN_WIDTH + 1; 
    uint8_t draw_h = SCREEN_HEIGHT + 1;
    if (draw_w > width) draw_w = width;
    if (draw_h > height) draw_h = height;

    set_bkg_submap(0, 0, draw_w, draw_h, map_data, width);
}

