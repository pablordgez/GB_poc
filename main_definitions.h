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
#define GET_RIGHT CONCAT(GetRight_, FILE_NAME)
#define GET_BOTTOM CONCAT(GetBottom_, FILE_NAME)
#define COLLIDER_ID CONCAT(_, FILE_NAME)
#define HANDLE_COLLISION CONCAT(HandleCollision_, FILE_NAME)

// function pointer returns void receives 

extern SpaceManager sprite_manager;
extern SpaceManager sprite_tile_manager;

typedef void (*RVoid_PVoid)(void);
typedef uint8_t (*RUINT8_T_PVOID)(void);
typedef uint16_t (*RUINT16_T_PVOID)(void);
extern RVoid_PVoid actor_update_functions[NUMBER_OF_ACTORS];
extern RUINT8_T_PVOID collider_check_functions[NUMBER_OF_COLLIDER_TYPES];
extern RVoid_PVoid collider_handle_functions[NUMBER_OF_ACTORS];
extern RUINT16_T_PVOID collider_right_functions[NUMBER_OF_COLLIDER_TYPES];
extern RUINT16_T_PVOID collider_bottom_functions[NUMBER_OF_COLLIDER_TYPES];
#define _ACTOR(name) \
    void Update_##name(void); \
    void HandleCollision_##name(void);
ACTORS

#undef _ACTOR

#define _COLLIDER(name) \
    uint8_t CheckCollider_##name(void); \
    uint16_t GetRight_##name(void); \
    uint16_t GetBottom_##name(void);
COLLIDERS
#undef _COLLIDER

void init_actor_functions(void);
void init_collider_functions(void);

extern uint8_t prev_joy;
extern uint8_t in_debug;



#endif /* MAIN_DEFINITIONS_H */