#include <gb/gb.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"


void init_player(Player* player, uint16_t x, uint16_t y, Animation *initial_animation){
    init_actor(&player->base, x, y, initial_animation);
}
void move_player(Player* player, int8_t dx, int8_t dy){
    move_actor(&player->base, dx, dy);
}
void update_player_frame(Player* player){
    update_actor_frame(&player->base);
}