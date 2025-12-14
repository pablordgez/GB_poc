#ifndef COLLIDER_H
#define COLLIDER_H
#include <stdint.h>
#include "collider_declarations.h"
#include "main_definitions.h"
typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t type;
    uint8_t is_blocking;
    uint8_t id;
} Collider;

extern Collider* THIS_COLLIDER;
extern Collider* THIS_COLLIDER_DETECTED;

#endif /* COLLIDER_H */