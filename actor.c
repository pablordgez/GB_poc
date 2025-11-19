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
  init_animation_runtime_data(actor->current_animation_runtime_data);
  set_animation_context(actor);
  load_animation(initial_animation, actor->drawX, actor->drawY);
}

void set_animation_context(Actor *actor) {
  THIS_ANIMATION = actor->current_animation;
  THIS_ANIMATION_RUNTIME_DATA = actor->current_animation_runtime_data;
}

void move_actor(Actor *actor, int8_t dx, int8_t dy) {
  if (dx < 0 && dx * -1 > actor->x) {
    actor->x = 0;
  } else {
    actor->x += dx;
  }
  if (dy < 0 && dy * -1 > actor->y) {
    actor->y = 0;
  } else {
    actor->y += dy;
  }
  set_animation_context(actor);
  if (actor->x > 4096)
    actor->x = 4096;
  if (actor->y > 4096)
    actor->y = 4096;
  actor->drawX = (actor->x >> 4) + 8 - camera_x;
  actor->drawY = (actor->y >> 4) + 16 - camera_y;

  uint16_t camera_x_shifted = camera_x << 4;
  uint16_t camera_y_shifted = camera_y << 4;
  uint16_t screen_width_shifted = SCREEN_WIDTH << 4;
  uint16_t screen_height_shifted = SCREEN_HEIGHT << 4;
  if (actor->x < camera_x_shifted ||
      actor->x > camera_x_shifted + screen_width_shifted ||
      actor->y < camera_y_shifted ||
      actor->y > camera_y_shifted + screen_height_shifted) {
    hide_animation();
    return;
  }
  move_animation_sprite(actor->drawX, actor->drawY);
}

void update_actor_frame(Actor *actor) {
  set_animation_context(actor);
  actor->drawX = (actor->x >> 4) + 8 - camera_x;
  actor->drawY = (actor->y >> 4) + 16 - camera_y;
  uint16_t camera_x_shifted = camera_x << 4;
  uint16_t camera_y_shifted = camera_y << 4;
  uint16_t screen_width_shifted = SCREEN_WIDTH << 4;
  uint16_t screen_height_shifted = SCREEN_HEIGHT << 4;
  uint16_t half_width = get_half_width() << 4;
  uint16_t half_height = get_half_height() << 4;
  if (actor->x + half_width < camera_x_shifted ||
      actor->x - half_width > camera_x_shifted + screen_width_shifted ||
      actor->y + half_height < camera_y_shifted ||
      actor->y - half_height > camera_y_shifted + screen_height_shifted) {
    hide_animation();
    return;
  }
  if (THIS_ANIMATION->metasprite == (void *)0) {
    update_animation();
  } else {
    update_animation_metasprite(actor->drawX, actor->drawY);
  }
  move_animation_sprite(actor->drawX, actor->drawY);
}

void UPDATE(void) { update_actor_frame(THIS_ACTOR); }

void set_actor_animation(Animation *new_animation) {
  unload_animation(THIS_ACTOR->current_animation);
  THIS_ACTOR->current_animation = new_animation;
  init_animation_runtime_data(THIS_ACTOR->current_animation_runtime_data);
  load_animation(new_animation, THIS_ACTOR->drawX, THIS_ACTOR->drawY);
}
