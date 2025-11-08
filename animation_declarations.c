#include "animation_declarations.h"

#define _ACTOR(name, data) \
    Animation name##_normal;
ACTORS
#undef _ACTOR

#define _ACTOR(name, data) \
    [ASSET_##name] = &name##_normal,
Animation* animations[] = {
    ACTORS
};
#undef _ACTOR

void animation_initialization(void){
    init_animation_metasprite(animations[ASSET_player], 2, 60, ASSET_player, 2, 2);
    init_animation(animations[ASSET_smile_npc], 2, 120, ASSET_smile_npc);
}