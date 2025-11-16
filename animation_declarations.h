#ifndef ANIMATION_DECLARATIONS_H
#define ANIMATION_DECLARATIONS_H
#include "animation.h"
#include "space_manager.h"
#include "actor_declarations.h"
#include "asset_manager.h"
#include "player_anim_sides.h"
#include "player_anim_down.h"
#include "player_anim_up.h"
#include "sprite_no_movement.h"
#include "sprite_up.h"

#define ANIMATIONS \
    _ANIMATION(player_sides, player_anim_sides, 2, 60, 2, 2) \
    _ANIMATION(player_up, player_anim_up, 1, 60, 2, 2) \
    _ANIMATION(player_down, player_anim_down, 2, 60, 2, 2) \
    _ANIMATION(no_movement, sprite_no_movement, 1, 255) \
    _ANIMATION(movement_up, sprite_up, 2, 20) \

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
#endif