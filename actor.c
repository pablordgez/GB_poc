#include "actor.h"
#include <stdio.h>

Actor* THIS_ACTOR;

void init_actor(Actor* actor, uint16_t x, uint16_t y, Animation *initial_animation) {
    actor->x = x;
    actor->y = y;
    actor->drawX = (x >> 4) + 8;
    actor->drawY = (y >> 4) + 16;
    actor->current_animation = initial_animation;

    load_animation(initial_animation, actor->drawX, actor->drawY);
}

void move_actor(Actor* actor, int8_t dx, int8_t dy) {
    actor->x += dx;
    actor->y += dy;
    actor->drawX = (actor->x >> 4) + 8;
    actor->drawY = (actor->y >> 4) + 16;
    THIS_ANIMATION = actor->current_animation;
    move_animation_sprite(actor->drawX, actor->drawY);
}

void update_actor_frame(Actor* actor) {
    THIS_ANIMATION = actor->current_animation;
    if(THIS_ANIMATION->metasprite == (void*) 0){
        update_animation();
    } else{
        update_animation_metasprite(actor->drawX, actor->drawY);
    }
}

void UPDATE(void) {
    update_actor_frame(THIS_ACTOR);
}

void set_actor_animation(Animation* new_animation) {
    unload_animation(THIS_ACTOR->current_animation);
    THIS_ACTOR->current_animation = new_animation;
    load_animation(new_animation, THIS_ACTOR->drawX, THIS_ACTOR->drawY);
}

