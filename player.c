#include <gb/gb.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

uint8_t changed_palette;


void init_player(Player* player, uint16_t x, uint16_t y, Animation *initial_animation){
    init_actor(&player->base, x, y, initial_animation);
    enable_actor(player);
    changed_palette = 0;
}

void UPDATE(void) {
    Player* THIS_PLAYER = (Player*)THIS_ACTOR;
    update_actor_frame(THIS_PLAYER);
    if(joypad() & J_RIGHT) {
            move_actor(THIS_PLAYER, 10, 0);
        }
        if(joypad() & J_LEFT) {
            move_actor(THIS_PLAYER, -10, 0);
        }
        if(joypad() & J_UP) {
            move_actor(THIS_PLAYER, 0, -10);
        }
        if(joypad() & J_DOWN) {
            move_actor(THIS_PLAYER, 0, 10);
        }
        if(joypad() & J_A) {
            printf("Player position: (%u, %u)\n", THIS_PLAYER->base.x, THIS_PLAYER->base.y);
        }
        if(joypad() & J_B && !(prev_joy & J_B)) {
            if(changed_palette == 0){
                OBP0_REG = DMG_PALETTE(DMG_BLACK, DMG_DARK_GRAY, DMG_LITE_GRAY, DMG_WHITE);
                changed_palette = 1;
            }
            else{
                OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY,  DMG_BLACK );
                changed_palette = 0;
            }
        }
        prev_joy = joypad();
    
}