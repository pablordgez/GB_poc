#include "main_definitions.h"
SpaceManager sprite_manager;
SpaceManager sprite_tile_manager;
RVoid_PVoid actor_update_functions[NUMBER_OF_ACTORS];
RUINt8_T_PVOID collider_check_functions[NUMBER_OF_COLLIDER_TYPES];
uint8_t prev_joy;
uint8_t in_debug = 0;
#define _ACTOR(name) \
    actor_update_functions[_##name] = Update_##name;
void init_actors_update_functions(void){
    ACTORS
}
#undef _ACTOR
#define _COLLIDER(name) \
    collider_check_functions[_##name] = CheckCollider_##name;
void init_collider_check_functions(void){
    COLLIDERS
}
#undef _COLLIDER