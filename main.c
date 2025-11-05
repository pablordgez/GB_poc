#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include "player.h"
#include "metasprite1.h"
#include "smile.h"
#include "space_manager.h"

void main(void)
{
    // Loop forever
    while(1){
        if(joypad() & J_START){
            break;
        }
        wait_vbl_done();
    }
    SpaceManager sprite_manager;
    init_space_manager(&sprite_manager, MAX_HARDWARE_SPRITES);
    SpaceManager sprite_tile_manager;
    init_space_manager_no_data(&sprite_tile_manager, 128);
    uint8_t player_sprite_slot = get_free_space(&sprite_manager, 4);
    register_space(&sprite_manager, 0, metasprite1_1_get_tiles());
    register_space(&sprite_manager, 4, metasprite1_2_get_tiles());
    uint8_t player_sprite_1_tile = get_free_space(&sprite_tile_manager, 8);
    register_space_no_data(&sprite_tile_manager, 8);
    Player p;
    init_player(&p, 1280, 1152, 2, 2, player_sprite_slot, player_sprite_1_tile, 2, 60, &sprite_manager);


    uint8_t smile_sprite_slot = get_free_space(&sprite_manager, 1);
    register_space(&sprite_manager, 0, get_smile_sprite());
    register_space(&sprite_manager, 1, get_smile_serious());
    uint8_t smile_sprite_tile = get_free_space(&sprite_tile_manager, 2);
    register_space_no_data(&sprite_tile_manager, 2);
    Actor a;
    init_actor(&a, 1600, 1152, 1, 1, smile_sprite_slot, smile_sprite_tile, 2, 120, &sprite_manager);

    free_space_manager(&sprite_manager);
    free_space_manager(&sprite_tile_manager);

    DISPLAY_ON;
    SHOW_SPRITES;
    while(1) {
        vsync();
        if(joypad() & J_RIGHT) {
            move_player(&p, 10, 0);
        }
        if(joypad() & J_LEFT) {
            move_player(&p, -10, 0);
        }
        if(joypad() & J_UP) {
            move_player(&p, 0, -10);
        }
        if(joypad() & J_DOWN) {
            move_player(&p, 0, 10);
        }
        if(joypad() & J_A) {
            printf("Player position: (%u, %u)\n", p.base.x, p.base.y);
        }
        update_player(&p);
        update_actor(&a);
    }
}
