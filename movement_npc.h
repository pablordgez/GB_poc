#include "actor.h"
#include "actor_manager.h"
#include "animation_declarations.h"

typedef struct
{
    Actor base;
    Animation* no_movement;
    Animation* movement_up;
} Movement_NPC;

void init_movement_npc(Movement_NPC* npc, uint16_t x, uint16_t y, Animation *initial_animation);