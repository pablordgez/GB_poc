#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include "sprite_manager.h"
#include "player.h"
#include "metasprite1.h"
#include "smile.h"
#include "tile_manager.h"

void main(void)
{
    // Loop forever
    while(1){
        if(joypad() & J_START){
            break;
        }
        wait_vbl_done();
    }
    SpriteManager sprite_manager;
    init_sprite_manager(&sprite_manager, 4);
    TileManager tile_manager;
    init_tile_manager(&tile_manager, 40);
    SpriteEntry character_entry = {0, metasprite1_1_get_tiles()};
    SpriteEntry character_entry2 = {1, metasprite1_2_get_tiles()};
    SpriteEntry smile_entry1 = {4, get_smile_sprite()};
    SpriteEntry smile_entry2 = {5, get_smile_serious()};
    add_sprite(&sprite_manager, character_entry);
    add_sprite(&sprite_manager, character_entry2);
    add_sprite(&sprite_manager, smile_entry1);
    add_sprite(&sprite_manager, smile_entry2);
    Player p;
    uint8_t free_tile_position = get_free_tiles_position(&tile_manager, 8);
    TileEntry new_tile = {free_tile_position, 8};
    register_tiles(&tile_manager, new_tile);
    init_player(&p, 1280, 1152, 2, 2, 0, free_tile_position, 2, 60, &sprite_manager);
    Actor a;
    free_tile_position = get_free_tiles_position(&tile_manager, 2);
    init_actor(&a, 1600, 1152, 1, 1, 4, free_tile_position, 2, 120, &sprite_manager);
    free_sprite_manager(&sprite_manager);
    free_tile_manager(&tile_manager);

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
