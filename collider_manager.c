#include "collider_manager.h"
uint8_t active_collider_number = 0;
uint8_t active_blocking_collider_number = 0;
Collider* active_colliders[MAX_ACTIVE_COLLIDERS];
Collider* active_blocking_colliders[MAX_ACTIVE_BLOCKING_COLLIDERS];


void enable_collider(Collider* collider){
    if(collider->is_blocking){
        if(active_blocking_collider_number < MAX_ACTIVE_BLOCKING_COLLIDERS){
            active_blocking_colliders[active_blocking_collider_number++] = collider;
        }
        return;
    }
    if(active_collider_number < MAX_ACTIVE_COLLIDERS){
        active_colliders[active_collider_number++] = collider;
    }
}

void disable_collider(Collider* collider){
    if(collider->is_blocking){
        for(uint8_t i = 0; i < active_blocking_collider_number; i++){
            if(active_blocking_colliders[i] == collider){
                active_blocking_colliders[i] = active_blocking_colliders[--active_blocking_collider_number];
                break;
            }
        }
        return;
    }
    for(uint8_t i = 0; i < active_collider_number; i++){
        if(active_colliders[i] == collider){
            active_colliders[i] = active_colliders[--active_collider_number];
            break;
        }
    }
}

uint8_t check_blocking_collisions(void){
    for(uint8_t i = 0; i < active_blocking_collider_number; i++){
        THIS_COLLIDER = active_blocking_colliders[i];
        if(collider_check_functions[THIS_COLLIDER->type]()){
            THIS_COLLIDER_DETECTED = THIS_COLLIDER;
            collider_handle_functions[THIS_ACTOR->actor_type_id]();
            return 1;
        }
    }
    return 0;
}

void check_collisions(void){
    for(uint8_t i = 0; i < active_collider_number; i++){
        THIS_COLLIDER = active_colliders[i];
        if(collider_check_functions[THIS_COLLIDER->type]()){
            THIS_COLLIDER_DETECTED = THIS_COLLIDER;
            collider_handle_functions[THIS_ACTOR->actor_type_id]();
        }
    }
}
