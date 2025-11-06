#include "space_manager.h"

void init_space_manager(SpaceManager* manager, uint8_t spaces) {
    manager->spaces = spaces;
    manager->memory_spaces = spaces;
    manager->last_allocated = 0;
    manager->used_memory_spaces = 0;
    manager->space_data = (SpaceEntry*)malloc(spaces * sizeof(SpaceEntry));
    if(!manager->space_data) {
        manager->spaces = 0;
    }
}

void init_space_manager_no_data(SpaceManager* manager, uint8_t spaces) {
    manager->spaces = spaces;
    manager->last_allocated = 0;
    manager->space_data = (void*)0;
}

void free_space_manager(SpaceManager* manager) {
    free(manager->space_data);
    manager->spaces = 0;
    manager->last_allocated = 0;
}

uint8_t get_free_space(SpaceManager* manager, uint8_t size) {
    if(manager->last_allocated + size > manager->spaces) {
        return 0; // Not enough space
    }
    return manager->last_allocated;
}

void register_space(SpaceManager* manager, uint8_t size, const uint8_t* data, uint8_t bank) {
    if(manager->space_data == (void*)0) {
        return; // Space manager not initialized with data
    }
    SpaceEntry entry = {data, manager->last_allocated, bank};
    if(manager->last_allocated + size > manager->spaces) {
        return; // Not enough space
    }
    if(manager->used_memory_spaces + 1 > manager->memory_spaces) {
        // reallocate memory
        uint8_t new_size = manager->memory_spaces * 2;
        SpaceEntry* new_space_data = (SpaceEntry*)realloc(manager->space_data, new_size * sizeof(SpaceEntry));
        if(!new_space_data) {
            return; // Memory allocation failed
        }
        manager->space_data = new_space_data;
        manager->memory_spaces = new_size;
    }
    manager->space_data[manager->used_memory_spaces] = entry;
    manager->last_allocated += size;
    manager->used_memory_spaces += 1;
}

void register_space_no_data(SpaceManager* manager, uint8_t size) {
    if(manager->last_allocated + size > manager->spaces) {
        return; // Not enough space
    }
    manager->last_allocated += size;
    manager->used_memory_spaces += 1;
}

const SpaceEntry* get_space_entry(SpaceManager* manager, uint8_t slot, uint8_t offset) {
    for(uint8_t i = 0; i < manager->used_memory_spaces; i++) {
        if(manager->space_data[i].slot == slot){
            if(i + offset >= manager->used_memory_spaces) {
                return (void*)0; // Offset out of bounds
            }
            return &manager->space_data[i + offset];
        }
    }
    return (void*)0; // Slot not found
}
