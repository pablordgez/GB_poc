#include "smile_npc.h"
void init_smile_npc(Smile_NPC* npc, uint16_t x, uint16_t y, Animation *initial_animation){
    init_actor(&npc->base, x, y, initial_animation);
    enable_actor(npc);
}

void UPDATE(void) {
    Smile_NPC* THIS_NPC = (Smile_NPC*)THIS_ACTOR;
    update_actor_frame(THIS_NPC);
}