#ifndef SPACE_MANAGER_H
#define SPACE_MANAGER_H
#include <stdint.h>
#include <stdlib.h>

typedef struct{
    uint8_t* data;
    uint8_t slot;
} SpaceEntry;

typedef struct{
    uint8_t spaces;
    uint8_t memory_spaces;
    uint8_t last_allocated;
    uint8_t used_memory_spaces;
    SpaceEntry* space_data;
} SpaceManager;


void init_space_manager(SpaceManager* manager, uint8_t spaces);
void init_space_manager_no_data(SpaceManager* manager, uint8_t spaces);
uint8_t get_free_space(SpaceManager* manager, uint8_t size);
void register_space(SpaceManager* manager, uint8_t size, uint8_t* data);
void register_space_no_data(SpaceManager* manager, uint8_t size);
void free_space_manager(SpaceManager* manager);
uint8_t* get_space_data(SpaceManager* manager, uint8_t slot, uint8_t offset);
#endif