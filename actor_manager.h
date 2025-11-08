#ifndef ACTOR_MANAGER_H
#define ACTOR_MANAGER_H
#include <stdint.h>
#include <gb/gb.h>
#include "actor.h"
#include "main_definitions.h"




void enable_actor(Actor* actor);
void disable_actor(Actor* actor);
void update_actors(void);

#endif // ACTOR_MANAGER_H