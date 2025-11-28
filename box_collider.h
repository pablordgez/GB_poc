#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H
#include "collider.h"
#include "actor.h"
typedef struct {
    Collider base;
    uint8_t width;
    uint8_t height;
} BoxCollider;

void init_box_collider(BoxCollider* box_collider, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
#endif /* BOX_COLLIDER_H */