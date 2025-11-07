#include "actor.h"
#include <stdio.h>

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
    move_animation_sprite(actor->current_animation, actor->drawX, actor->drawY);
}

void update_actor_frame(Actor* actor) {
    if(actor->current_animation->metasprite == (void*) 0){
        update_animation(actor->current_animation);
    } else{
        update_animation_metasprite(actor->current_animation, actor->drawX, actor->drawY);
    }
    
}