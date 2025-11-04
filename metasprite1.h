#define TileLabelBank 0
#include <stdint.h>
#include <gb/gb.h>

extern uint8_t metasprite1_1[];
extern uint8_t metasprite1_2[];
uint8_t* metasprite1_1_get_tiles(void) BANKED;
uint8_t* metasprite1_2_get_tiles(void) BANKED;
