#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include "player.h"
#include "map.h"
#include "map1.h"
#include "animation_declarations.h"
#include "main_definitions.h"
#include "actor_manager.h"
#include "movement_npc.h"
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
    init_space_manager(&sprite_manager, MAX_HARDWARE_SPRITES);
    init_space_manager(&sprite_tile_manager, 128);
    animation_initialization();
    init_actors_update_functions();
    Player p;
    init_player(&p, 1280, 1152, animations[_player_sides]);
    Movement_NPC a, b, c, d;
    init_movement_npc(&a, 300, 1152, animations[_no_movement]);
    init_movement_npc(&b, 3000, 1152, animations[_no_movement]);
    init_movement_npc(&c, 1280, 300, animations[_no_movement]);
    init_movement_npc(&d, 1280, 3000, animations[_no_movement]);

    Map map;
    init_map(&map, 32, 32, map1_tileset, map1_tilemap);

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;

    uint8_t changed_palette = 0;
    prev_joy = 0;

    while(1) {
        vsync();
        update_actors();
        prev_joy = joypad();
        
        
    }
}
