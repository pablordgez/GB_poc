#ifndef COLLIDER_H
#define COLLIDER_H
#include <stdint.h>
#include "collider_declarations.h"
#include "main_definitions.h"
typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t type;
} Collider;

Collider* THIS_COLLIDER;
#endif /* COLLIDER_H */