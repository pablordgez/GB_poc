#include "actor_manager.h"

uint8_t active_actor_number = 0;
Actor* active_actors[MAX_HARDWARE_SPRITES];

void enable_actor(Actor* actor) {
    if(active_actor_number < MAX_HARDWARE_SPRITES){
        active_actors[active_actor_number++] = actor;
    }
}
void disable_actor(Actor* actor) {
    for (uint8_t i = 0; i < active_actor_number; i++) {
        if (active_actors[i] == actor) {
            active_actors[i] = active_actors[--active_actor_number];
            break;
        }
    }
}

void update_actors(void){
    for(uint8_t i = 0; i < active_actor_number; i++){
        THIS_ACTOR = active_actors[i];
        actor_update_functions[THIS_ACTOR->actor_type_id]();
    }
}