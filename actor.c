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
    if(dx < 0 && dx * -1 > actor->x) {
        actor->x = 0;
    } else {
        actor->x += dx;
    }
    if(dy < 0 && dy * -1 > actor->y) {
        actor->y = 0;
    } else {
        actor->y += dy;

    }
    THIS_ANIMATION = actor->current_animation;
    if(actor->x > 4096) actor->x = 4096;
    if(actor->y > 4096) actor->y = 4096;
    actor->drawX = (actor->x >> 4) + 8 - camera_x;
    actor->drawY = (actor->y >> 4) + 16 - camera_y;
    
    if(((actor->x >> 4) > 192 || (actor->y >> 4) > 176)) {
        hide_animation();
        return;
    }
    move_animation_sprite(actor->drawX, actor->drawY);
}

void update_actor_frame(Actor* actor) {
    THIS_ANIMATION = actor->current_animation;
    actor->drawX = (actor->x >> 4) + 8 - camera_x;
    actor->drawY = (actor->y >> 4) + 16 - camera_y;
    if(actor->drawX){
        hide_animation();
        return;
    }
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

