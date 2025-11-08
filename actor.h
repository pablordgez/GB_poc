#ifndef ACTOR_H
#define ACTOR_H
#include <stdint.h>
#include <gb/metasprites.h>
#include <gb/gb.h>
#include <stdlib.h>
#include "space_manager.h"
#include "animation.h"
#include "main_definitions.h"


typedef struct{
    uint16_t x;
    uint16_t y;
    uint8_t drawX;
    uint8_t drawY;
    Animation* current_animation;
    uint8_t enabled;
} Actor;

extern Actor* THIS_ACTOR;

void init_actor(Actor* actor, uint16_t x, uint16_t y, Animation *initial_animation);
void move_actor(Actor* actor, int8_t dx, int8_t dy);
void update_actor_frame(Actor* actor);
#endif /* ACTOR_H */