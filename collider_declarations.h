#ifndef COLLIDER_DECLARATIONS_H
#define COLLIDER_DECLARATIONS_H
#define COLLIDERS \
    _COLLIDER(box_collider) \

#define _COLLIDER(name) _##name,
    enum{
        COLLIDERS
        NUMBER_OF_COLLIDER_TYPES
    };
#undef _COLLIDER
#endif /* COLLIDER_DECLARATIONS_H */