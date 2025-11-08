#ifndef MAIN_DEFINITIONS_H
#define MAIN_DEFINITIONS_H
#include "space_manager.h"
#include "actor_declarations.h"
#define _CONCAT_DELAY(A,B) A ## B
#define CONCAT(A,B) _CONCAT_DELAY(A,B)
#define ACTOR_ID CONCAT(_, FILE_NAME)
#define UPDATE CONCAT(Update_, FILE_NAME)

// function pointer returns void receives 

extern SpaceManager sprite_manager;
extern SpaceManager sprite_tile_manager;

typedef void (*RVoid_PVoid)(void);
extern RVoid_PVoid actor_update_functions[NUMBER_OF_ACTORS];
#define _ACTOR(name, data) \
    void Update_##name(void);

ACTORS

#undef _ACTOR

void init_actors_update_functions(void);

extern uint8_t prev_joy;



#endif /* MAIN_DEFINITIONS_H */