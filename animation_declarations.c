#include "animation_declarations.h"

Animation player_normal;
Animation smile_normal;

Animation* animations[] = {
    [ASSET_METASPRITE1] = &player_normal,
    [ASSET_SMILE] = &smile_normal
};


void animation_initialization(void){
    init_animation_metasprite(animations[ASSET_METASPRITE1], 2, 60, ASSET_METASPRITE1, 2, 2);
    init_animation(animations[ASSET_SMILE], 2, 120, ASSET_SMILE);
}