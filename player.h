#include "actor.h"
#include "actor_manager.h"
#include "animation_declarations.h"
typedef struct player
{
    Actor base;
    Animation* animation_sides;
    Animation* animation_up;
    Animation* animation_down;
    uint8_t prev_direction;
} Player;

void init_player(Player* player, uint16_t x, uint16_t y, Animation *initial_animation);
extern uint8_t changed_palette;