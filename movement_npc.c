#pragma bank 255
#include "movement_npc.h"
#include "stdio.h"
void init_movement_npc(Movement_NPC* npc, uint16_t x, uint16_t y, Animation *initial_animation){
    init_actor(&npc->base, x, y, initial_animation);
    npc->base.actor_type_id = ACTOR_ID;
    enable_actor(npc);
    npc->no_movement = animations[_no_movement];
    npc->movement_up = animations[_movement_up];
}

void UPDATE(void) {
    Movement_NPC* THIS_NPC = (Movement_NPC*)THIS_ACTOR;
    update_actor_frame(THIS_NPC);
    if((joypad() & J_UP) && !(prev_joy & J_UP)) {
        if(THIS_NPC->base.current_animation != THIS_NPC->movement_up){
            set_actor_animation(THIS_NPC->movement_up);
        }
    } else if(!(joypad() & J_UP)) {
        if(THIS_NPC->base.current_animation != THIS_NPC->no_movement){
            set_actor_animation(THIS_NPC->no_movement);
        }
    }
}