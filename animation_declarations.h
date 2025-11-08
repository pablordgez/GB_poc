#include "animation.h"
#include "space_manager.h"
#include "actor_declarations.h"
#include "asset_manager.h"

#include "metasprite1.h"
#include "smile.h"

#define ANIMATIONS \
    _ANIMATION(player_idle, metasprite_1, 2, 60, 2, 2) \
    _ANIMATION(smile_npc_idle, smile_sprite, 2, 120)

#define _ANIMATION(name, data, frames, duration, ...) _##name,
    enum{
        ANIMATIONS

        NUMBER_OF_ANIMATIONS
    };
#undef _ANIMATION

extern Animation* animations[];

void animation_initialization(void);
//Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t animation_id
#define _ANIMATION_FUNC(name, data, frames, duration) \
    init_animation(animations[_##name], frames, duration, _##name);

#define _ANIMATION_FUNC_MSPR(name, data, frames, duration, width, height) \
    init_animation_metasprite(animations[_##name], frames, duration, _##name, width, height);

#define GET_MACRO_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME