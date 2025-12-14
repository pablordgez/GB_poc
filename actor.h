#ifndef ACTOR_H
#define ACTOR_H
#include "animation.h"
#include "camera.h"
#include "main_definitions.h"
#include "space_manager.h"
#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdint.h>
#include <stdlib.h>
#include "collider.h"
#include "collider_manager.h"

typedef struct {
  uint16_t x;
  uint16_t y;
  uint8_t drawX;
  uint8_t drawY;
  Animation *current_animation;
  AnimationRuntimeData *current_animation_runtime_data;
  uint8_t enabled;
  uint8_t actor_type_id;
  uint8_t was_colliding;
} Actor;

extern Actor *THIS_ACTOR;

void init_actor(Actor *actor, uint16_t x, uint16_t y,
                Animation *initial_animation);
void move_actor(Actor *actor, int8_t dx, int8_t dy);
void update_actor_frame(Actor *actor);
void set_actor_animation(Animation *new_animation);
void set_animation_context(Actor *actor);
void draw_actor(void);
#endif /* ACTOR_H */