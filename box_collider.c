#include "box_collider.h"
void init_box_collider(BoxCollider* box_collider, uint8_t x, uint8_t y, uint8_t width, uint8_t height){
    box_collider->base.x = x;
    box_collider->base.y = y;
    box_collider->base.type = COLLIDER_ID;
    box_collider->width = width;
    box_collider->height = height;
}

uint8_t CHECK_COLLIDER(void){
    if(THIS_ACTOR->x < THIS_COLLIDER->x + ((BoxCollider*)THIS_COLLIDER)->width &&
       THIS_ACTOR->x + get_half_width() * 2 > THIS_COLLIDER->x &&
       THIS_ACTOR->y < THIS_COLLIDER->y + ((BoxCollider*)THIS_COLLIDER)->height &&
       THIS_ACTOR->y + get_half_height() * 2 > THIS_COLLIDER->y) {
        return 1;
    }
    return 0;
}