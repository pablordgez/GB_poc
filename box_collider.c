#include "box_collider.h"
void init_box_collider(BoxCollider* box_collider, uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint8_t is_blocking, uint8_t id){
    box_collider->base.x = x;
    box_collider->base.y = y;
    box_collider->base.type = COLLIDER_ID;
    box_collider->width = width;
    box_collider->height = height;
    box_collider->base.is_blocking = is_blocking;
    box_collider->base.id = id;
    enable_collider((Collider*)box_collider);
}

uint8_t CHECK_COLLIDER(void){
    uint16_t adjusted_width = ((BoxCollider*)THIS_COLLIDER)->width << 4;
    uint16_t adjusted_height = ((BoxCollider*)THIS_COLLIDER)->height << 4;
    if(THIS_ACTOR->x - (get_half_width() << 4) + (THIS_ANIMATION->padding_left << 4) < THIS_COLLIDER->x + adjusted_width &&
       THIS_ACTOR->x + (get_half_width() << 4) - (THIS_ANIMATION->padding_right << 4) > THIS_COLLIDER->x &&
       THIS_ACTOR->y - (get_half_height() << 4) + (THIS_ANIMATION->padding_top << 4) < THIS_COLLIDER->y + adjusted_height &&
       THIS_ACTOR->y + (get_half_height() << 4) - (THIS_ANIMATION->padding_bottom << 4) > THIS_COLLIDER->y) {
        return 1;
    }
    return 0;
}

uint16_t GET_RIGHT(void){
    return THIS_COLLIDER->x + (((BoxCollider*)THIS_COLLIDER)->width << 4);
}

uint16_t GET_BOTTOM(void){
    return THIS_COLLIDER->y + (((BoxCollider*)THIS_COLLIDER)->height << 4);
}