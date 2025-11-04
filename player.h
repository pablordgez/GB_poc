#include "sprite_manager.h"
#include <gb/metasprites.h>
struct player
{
    uint16_t x;
    uint16_t y;
    uint8_t width;
    uint8_t height;
    uint8_t drawX;
    uint8_t drawY;
    uint8_t sprite_id;
    uint8_t first_tile;
    uint8_t num_sprites;
    uint8_t current_sprite;
    uint8_t frames_per_sprite;
    uint8_t current_frame;
    metasprite_t* metasprite;
};

void init_player(struct player* p, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t sprite_id, uint8_t first_tile, uint8_t num_sprites, uint8_t frames_per_sprite, SpriteManager* sprite_manager);
void init_metasprite(struct player* p);
void move_player(struct player* p, int8_t dx, int8_t dy);
void update_player(struct player* p);
