#include "actor.h"
#include <stdio.h>

Actor *THIS_ACTOR;

void init_actor(Actor *actor, uint16_t x, uint16_t y,
                Animation *initial_animation) {
  actor->x = x;
  actor->y = y;
  actor->drawX = (x >> 4) + 8;
  actor->drawY = (y >> 4) + 16;
  actor->current_animation = initial_animation;
  actor->current_animation_runtime_data = malloc(sizeof(AnimationRuntimeData));
  actor->was_colliding = 0;
  init_animation_runtime_data(actor->current_animation_runtime_data);
  set_animation_context(actor);
  load_animation(initial_animation, actor->drawX, actor->drawY);
}

void set_animation_context(Actor *actor) {
  THIS_ANIMATION = actor->current_animation;
  THIS_ANIMATION_RUNTIME_DATA = actor->current_animation_runtime_data;
}

void move_actor(Actor *actor, int8_t dx, int8_t dy) {
  uint8_t half_width = get_half_width() << 4;
  uint8_t half_height = get_half_height() << 4;
  if (dx < 0 && dx * -1 + half_width > actor->x) {
    actor->x = half_width;
  } else if (dx != 0) {
    actor->x += dx;
    if (actor->x > 4096 - half_width){
      actor->x = 4096 - half_width;
    }
    if(check_blocking_collisions()){
      if(dx > 0){
        actor->x = THIS_COLLIDER_DETECTED->x - half_width + (THIS_ACTOR->current_animation->padding_right << 4);
      } else{
        actor->x = collider_right_functions[THIS_COLLIDER_DETECTED->type]() + half_width - (THIS_ACTOR->current_animation->padding_left << 4);
      }
    }
  } 
  if (dy < 0 && dy * -1 + half_height > actor->y) {
    actor->y = half_height;
  } else if (dy != 0) {
    actor->y += dy;
    if (actor->y > 4096 - half_height){
      actor->y = 4096 - half_height;
    }
    if(check_blocking_collisions()){
      if(dy > 0){
        actor->y = THIS_COLLIDER_DETECTED->y - half_height + (THIS_ACTOR->current_animation->padding_bottom << 4);
      } else{
        actor->y = collider_bottom_functions[THIS_COLLIDER_DETECTED->type]() + half_height - (THIS_ACTOR->current_animation->padding_top << 4);
      }
    }
  }
  
  
}

void draw_actor(void) {
  set_animation_context(THIS_ACTOR);
  THIS_ACTOR->drawX = (THIS_ACTOR->x >> 4) + 8 - camera_x;
  THIS_ACTOR->drawY = (THIS_ACTOR->y >> 4) + 16 - camera_y;
  uint16_t camera_x_shifted = camera_x << 4;
  uint16_t camera_y_shifted = camera_y << 4;
  uint16_t screen_width_shifted = SCREEN_WIDTH << 4;
  uint16_t screen_height_shifted = SCREEN_HEIGHT << 4;
  uint16_t half_width = get_half_width() << 4;
  uint16_t half_height = get_half_height() << 4;
  if (THIS_ACTOR->x + half_width < camera_x_shifted ||
      THIS_ACTOR->x - half_width > camera_x_shifted + screen_width_shifted ||
      THIS_ACTOR->y + half_height < camera_y_shifted ||
      THIS_ACTOR->y - half_height > camera_y_shifted + screen_height_shifted) {
    hide_animation();
    return;
  }
  move_animation_sprite(THIS_ACTOR->drawX, THIS_ACTOR->drawY);
}

void update_actor_frame(Actor *actor) {
  set_animation_context(actor);
  if (THIS_ANIMATION->metasprite == (void *)0) {
    update_animation();
  } else {
    update_animation_metasprite(actor->drawX, actor->drawY);
  }
}

void UPDATE(void) { update_actor_frame(THIS_ACTOR); }

void set_actor_animation(Animation *new_animation) {
  unload_animation(THIS_ACTOR->current_animation);
  THIS_ACTOR->current_animation = new_animation;
  init_animation_runtime_data(THIS_ACTOR->current_animation_runtime_data);
  load_animation(new_animation, THIS_ACTOR->drawX, THIS_ACTOR->drawY);
}
