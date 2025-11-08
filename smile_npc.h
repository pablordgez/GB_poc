#include "actor.h"
#include "actor_manager.h"

typedef struct
{
    Actor base;
} Smile_NPC;

void init_smile_npc(Smile_NPC* npc, uint16_t x, uint16_t y, Animation *initial_animation);