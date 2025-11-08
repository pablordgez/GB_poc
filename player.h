#include "actor.h"
#include "actor_manager.h"
typedef struct player
{
    Actor base;
} Player;

void init_player(Player* player, uint16_t x, uint16_t y, Animation *initial_animation);
extern uint8_t changed_palette;