#include <gb/gb.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

uint8_t changed_palette;


void init_player(Player* player, uint16_t x, uint16_t y, Animation *initial_animation){
    init_actor(&player->base, x, y, initial_animation);
    player->base.actor_type_id = ACTOR_ID;
    enable_actor(player);
    changed_palette = 0;
    player->animation_sides = animations[_player_sides];
    player->animation_up = animations[_player_up];
    player->animation_down = animations[_player_down];
    player->prev_direction = 1;
    player->current_direction = 1;
}

void UPDATE(void) {
    Player* THIS_PLAYER = (Player*)THIS_ACTOR;
    uint8_t input = joypad();
    update_actor_frame(THIS_PLAYER);
    int8_t dx = 0;
    int8_t dy = 0;
    if(input & J_RIGHT) {
        dx = 10;
    }
    if(input & J_LEFT) {
        dx = -10;
    }
    if(input & J_UP) {
        dy = -10;
    }
    if(input & J_DOWN) {
        dy = 10;
    }

    if(dx != 0 && dy != 0) {
        if(dx > 0) {
            dx = 7;
        } else {
            dx = -7;
        }
        if(dy > 0) {
            dy = 7;
            if(THIS_PLAYER->base.current_animation != THIS_PLAYER->animation_down){
                set_actor_animation(THIS_PLAYER->animation_down);
                THIS_PLAYER->prev_direction = THIS_PLAYER->current_direction;
                THIS_PLAYER->current_direction = 2;
            }
        } else {
            dy = -7;
            if(THIS_PLAYER->base.current_animation != THIS_PLAYER->animation_up){
                set_actor_animation(THIS_PLAYER->animation_up);
                THIS_PLAYER->prev_direction = THIS_PLAYER->current_direction;
                THIS_PLAYER->current_direction = 0;
            }
        }
    } else if(dx != 0) {
        if(THIS_PLAYER->base.current_animation != THIS_PLAYER->animation_sides){
            set_actor_animation(THIS_PLAYER->animation_sides);
        }
        if(dx > 0) {
            THIS_PLAYER->prev_direction = THIS_PLAYER->current_direction;
            THIS_PLAYER->current_direction = 1;
        } else {
            THIS_PLAYER->prev_direction = THIS_PLAYER->current_direction;
            THIS_PLAYER->current_direction = 3;
        }
    } else if(dy != 0) {
        if(dy > 0) {
            if(THIS_PLAYER->base.current_animation != THIS_PLAYER->animation_down){
                set_actor_animation(THIS_PLAYER->animation_down);
                THIS_PLAYER->prev_direction = THIS_PLAYER->current_direction;
                THIS_PLAYER->current_direction = 2;
            }
        } else {
            if(THIS_PLAYER->base.current_animation != THIS_PLAYER->animation_up){
                set_actor_animation(THIS_PLAYER->animation_up);
                THIS_PLAYER->prev_direction = THIS_PLAYER->current_direction;
                THIS_PLAYER->current_direction = 0;
            }
        }
    }
    move_actor(THIS_PLAYER, dx, dy);

    if(joypad() & J_A) {
        move_bkg(0, 0);
        printf("Player position: (%u, %u)\n", THIS_PLAYER->base.x, THIS_PLAYER->base.y);
        printf("Camera position: (%u, %u)\n", camera_x, camera_y);
        in_debug = 1;
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
    
    if(THIS_PLAYER->prev_direction == 3 && THIS_PLAYER->current_direction == 1){
        flip_animation_metasprite(0, 0);
    }
    else if(THIS_PLAYER->prev_direction != 3 && THIS_PLAYER->current_direction == 3){
        flip_animation_metasprite(1, 0);
    }
    update_camera(THIS_PLAYER->base.x, THIS_PLAYER->base.y);
    
}


void HANDLE_COLLISION(void){
    // No collision handling for this NPC
}