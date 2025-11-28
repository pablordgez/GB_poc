#ifndef MAIN_DEFINITIONS_H
#define MAIN_DEFINITIONS_H
#include "space_manager.h"
#include "actor_declarations.h"
#include "collider_declarations.h"
#define _CONCAT_DELAY(A,B) A ## B
#define CONCAT(A,B) _CONCAT_DELAY(A,B)
#define ACTOR_ID CONCAT(_, FILE_NAME)
#define UPDATE CONCAT(Update_, FILE_NAME)
#define CHECK_COLLIDER CONCAT(CheckCollider_, FILE_NAME)
#define COLLIDER_ID CONCAT(_, FILE_NAME)

// function pointer returns void receives 

extern SpaceManager sprite_manager;
extern SpaceManager sprite_tile_manager;

typedef void (*RVoid_PVoid)(void);
typedef uint8_t (*RUINt8_T_PVOID)(void);
extern RVoid_PVoid actor_update_functions[NUMBER_OF_ACTORS];
extern RUINt8_T_PVOID collider_check_functions[NUMBER_OF_COLLIDER_TYPES];
#define _ACTOR(name) \
    void Update_##name(void);

ACTORS

#undef _ACTOR

#define _COLLIDER(name) \
    uint8_t CheckCollider_##name(void);
COLLIDERS
#undef _COLLIDER

void init_actors_update_functions(void);
void init_collider_check_functions(void);

extern uint8_t prev_joy;
extern uint8_t in_debug;



#endif /* MAIN_DEFINITIONS_H */