#include "actor.h"
typedef struct player
{
    Actor base;
} Player;

void init_player(Player* p, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t sprite_id, uint8_t first_tile, uint8_t num_sprites, uint8_t frames_per_sprite, SpaceManager* sprite_manager);
void init_metasprite_player(Player* p);
void move_player(Player* p, int8_t dx, int8_t dy);
void update_player(Player* p);
