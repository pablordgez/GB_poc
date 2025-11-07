#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include "player.h"
#include "metasprite1.h"
#include "smile.h"
#include "space_manager.h"
#include "map.h"
#include "map1.h"
#include "animation_declarations.h"

void main(void)
{

    BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY);
    OBP0_REG =OBP1_REG =DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY,  DMG_BLACK );

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
    animation_initialization(&sprite_manager, &sprite_tile_manager);
    Player p;
    init_player(&p, 1280, 1152, animations[ASSET_METASPRITE1]);
    Actor a;
    init_actor(&a, 1600, 1152, animations[ASSET_SMILE]);

    /*
    BANKREF_EXTERN(metasprite1)
    BANKREF_EXTERN(smile)

    uint8_t player_sprite_slot = get_free_space(&sprite_manager, 4);
    uint8_t prev_bank = _current_bank;
    SWITCH_ROM(BANK(metasprite1));
    register_space(&sprite_manager, 0, metasprite1_1, _current_bank);
    register_space(&sprite_manager, 4, metasprite1_2, _current_bank);
    SWITCH_ROM(prev_bank);
    uint8_t player_sprite_1_tile = get_free_space(&sprite_tile_manager, 8);
    register_space_no_data(&sprite_tile_manager, 8);
    Player p;
    init_player(&p, 1280, 1152, 2, 2, player_sprite_slot, player_sprite_1_tile, 2, 60, &sprite_manager);


    uint8_t smile_sprite_slot = get_free_space(&sprite_manager, 1);
    prev_bank = _current_bank;
    SWITCH_ROM(BANK(smile));
    register_space(&sprite_manager, 0, smile_sprite, _current_bank);
    register_space(&sprite_manager, 1, smile_serious, _current_bank);
    SWITCH_ROM(prev_bank);
    uint8_t smile_sprite_tile = get_free_space(&sprite_tile_manager, 2);
    register_space_no_data(&sprite_tile_manager, 2);
    Actor a;
    init_actor(&a, 1600, 1152, 1, 1, smile_sprite_slot, smile_sprite_tile, 2, 120, &sprite_manager);

    free_space_manager(&sprite_manager);
    free_space_manager(&sprite_tile_manager);
    */

    Map map;
    init_map(&map, 32, 32, map1_tileset, map1_tilemap);

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;

    uint8_t changed_palette = 0;
    uint8_t prev_joy = 0;

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
        update_player_frame(&p);
        update_actor_frame(&a);
    }
}
