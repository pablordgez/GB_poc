#ifndef CAMERA_H
#define CAMERA_H
#include <stdint.h>
#include <gb/gb.h>
#include "main_definitions.h"
#include "map.h"


extern uint16_t camera_x;
extern uint16_t camera_y;
extern uint8_t limit_x;
extern uint8_t limit_y;
extern uint16_t max_cam_x;
extern uint16_t max_cam_y;
extern Map* active_map;
extern uint16_t old_camera_x;
extern uint16_t old_camera_y;

void set_active_map(Map* map);

void update_camera(uint16_t x, uint16_t y);
#endif /* CAMERA_H */