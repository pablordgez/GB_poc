#ifndef SPRITE_DECLARATIONS_H
#define SPRITE_DECLARATIONS_H
// This file should eventually be created by a script
#include <gb/gb.h>
#include "asset_manager.h"

#define ACTORS \
    _ACTOR(player) \
    _ACTOR(movement_npc)

#define _ACTOR(name) _##name,
    enum{
        ACTORS
        NUMBER_OF_ACTORS
    };
#undef _ACTOR

// breaking dependency loop
extern const AssetEntry animation_assets[];

#endif /* SPRITE_DECLARATIONS_H */