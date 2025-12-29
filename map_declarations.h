#ifndef MAP_DECLARATIONS_H
#define MAP_DECLARATIONS_H
#include "asset_manager.h"
#include "gb/gb.h"
#include "map.h"
#include "map1.h"
#define MAPS \
    _MAP(map1_, map1_tilemap, 64, 64)

#define _MAP(name, data, width, height) _##name,
    enum{
        MAPS

        NUMBER_OF_MAPS
    };
#undef _MAP

extern Map* maps[];
void map_initialization(void);
#endif /* MAP_DECLARATIONS_H */