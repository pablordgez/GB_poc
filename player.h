#include "actor.h"
typedef struct player
{
    Actor base;
} Player;

void init_player(Player* player, uint16_t x, uint16_t y, Animation *initial_animation);
void move_player(Player* player, int8_t dx, int8_t dy);
void update_player_frame(Player* player);
