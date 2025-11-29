#include "main_definitions.h"
SpaceManager sprite_manager;
SpaceManager sprite_tile_manager;
RVoid_PVoid actor_update_functions[NUMBER_OF_ACTORS];
RUINT8_T_PVOID collider_check_functions[NUMBER_OF_COLLIDER_TYPES];
RVoid_PVoid collider_handle_functions[NUMBER_OF_ACTORS];
RUINT16_T_PVOID collider_right_functions[NUMBER_OF_COLLIDER_TYPES];
RUINT16_T_PVOID collider_bottom_functions[NUMBER_OF_COLLIDER_TYPES];
uint8_t prev_joy;
uint8_t in_debug = 0;
#define _ACTOR(name) \
    actor_update_functions[_##name] = Update_##name; \
    collider_handle_functions[_##name] = HandleCollision_##name;

void init_actor_functions(void){
    ACTORS
}
#undef _ACTOR
#define _COLLIDER(name) \
    collider_check_functions[_##name] = CheckCollider_##name; \
    collider_right_functions[_##name] = GetRight_##name; \
    collider_bottom_functions[_##name] = GetBottom_##name;

void init_collider_functions(void){
    COLLIDERS
}
#undef _COLLIDER