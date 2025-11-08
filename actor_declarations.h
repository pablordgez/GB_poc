#ifndef SPRITE_DECLARATIONS_H
#define SPRITE_DECLARATIONS_H
// This file should eventually be created by a script
#include "asset_manager.h"
#include <gb/gb.h>

#include "metasprite1.h"
#include "smile.h"

#define ACTORS \
    _ACTOR(player, metasprite_1) \
    _ACTOR(smile_npc, smile_sprite)

#define _ACTOR(name, data) ASSET_##name,
enum{
    ACTORS

    NUMBER_OF_ACTORS
};
#undef _ACTOR

extern const AssetEntry actors[];
#endif /* SPRITE_DECLARATIONS_H */