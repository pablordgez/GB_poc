#include "animation_declarations.h"

#define _ANIMATION(name, data, frames, duration, ...) \
    Animation name;
ANIMATIONS
#undef _ANIMATION

#define _ANIMATION(name, data, frames, duration, ...) \
    [_##name] = &name,
Animation* animations[] = {
    ANIMATIONS
};
#undef _ANIMATION


BANKREF_EXTERN(player_idle)
BANKREF_EXTERN(smile_npc_idle)
#define _ANIMATION(name, data, frames, duration, ...) \
    [_##name] = { BANK(name), data },
const AssetEntry animation_assets [] = {
    ANIMATIONS
};
#undef _ANIMATION


#define _ANIMATION(...) GET_MACRO_IMPL(__VA_ARGS__, \
    _ANIMATION_FUNC_MSPR, \
    _ANIMATION_FUNC_MSPR, \
    _ANIMATION_FUNC, \
    _ANIMATION_FUNC, \
    _ANIMATION_FUNC, \
    _ANIMATION_FUNC, \
    _ANIMATION_FUNC \
) (__VA_ARGS__)


void animation_initialization(void){
    ANIMATIONS
}
#undef _ANIMATION