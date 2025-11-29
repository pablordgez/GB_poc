#ifndef COLLIDER_MANAGER_H
#define COLLIDER_MANAGER_H
#include "collider.h"
#include "main_definitions.h"
#include "actor.h"

void enable_collider(Collider* collider);
void disable_collider(Collider* collider);
uint8_t check_blocking_collisions(void);
void check_collisions(void);
#endif // COLLIDER_MANAGER_H