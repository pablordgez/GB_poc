#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t position;
    uint8_t size;
} TileEntry;


typedef struct {
    uint8_t total_tiles;
    TileEntry* registered_tiles;
    uint8_t registered_count;
} TileManager;



void init_tile_manager(TileManager* manager, uint8_t total_tiles);
void register_tiles(TileManager* manager, TileEntry tiles);
uint8_t get_free_tiles_position(TileManager* manager, uint8_t size);
void free_tile_manager(TileManager* manager);