#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include "sprite_manager.h"
#include "player.h"
#include "metasprite1.h"


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
    init_sprite_manager(&sprite_manager, 2);
    SpriteEntry character_entry = {0, metasprite1_1_get_tiles()};
    SpriteEntry character_entry2 = {1, metasprite1_2_get_tiles()};
    add_sprite(&sprite_manager, character_entry);
    add_sprite(&sprite_manager, character_entry2);
    struct player p;
    init_player(&p, 1280, 1152, 2, 2, 0, 0, 2, 60, &sprite_manager);
    free_sprite_manager(&sprite_manager);

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
        update_player(&p);
    }
}
