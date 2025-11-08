#include "main_definitions.h"
SpaceManager sprite_manager;
SpaceManager sprite_tile_manager;
RVoid_PVoid actor_update_functions[NUMBER_OF_ACTORS];
uint8_t prev_joy;

#define _ACTOR(name, data) \
    actor_update_functions[_##name] = Update_##name;
void init_actors_update_functions(void){
    ACTORS
}
#undef _ACTOR