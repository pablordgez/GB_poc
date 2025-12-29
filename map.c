#include "map.h"


void init_map(Map* map, uint16_t width, uint16_t height, const uint8_t* map_data, uint8_t id) {
    
    map->width = width;
    map->height = height;
    map->map_data = map_data;
    map->id = id;

}

void load_map(Map* map, uint8_t* tiles, uint8_t num_tiles){
    uint8_t prev_bank = _current_bank;
    const AssetEntry* data_entry = &map_assets[map->id];
    SWITCH_ROM(data_entry->bank);
    if (num_tiles > 0) {
        set_bkg_data(0, num_tiles, tiles);
    }

    uint8_t draw_w = (SCREEN_WIDTH >> 3) + 1; 
    uint8_t draw_h = (SCREEN_HEIGHT >> 3) + 1;
    if (draw_w > map->width) draw_w = map->width;
    if (draw_h > map->height) draw_h = map->height;

    set_bkg_submap(0, 0, draw_w, draw_h, map->map_data, map->width);
    SWITCH_ROM(prev_bank);

}

