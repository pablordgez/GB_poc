#ifndef CAMERA_H
#define CAMERA_H
#include <stdint.h>
#include <gb/gb.h>
#include "main_definitions.h"
extern uint8_t camera_x;
extern uint8_t camera_y;
extern uint8_t limit_x;
extern uint8_t limit_y;
extern uint8_t max_cam_x;
extern uint8_t max_cam_y;

void update_camera(uint16_t x, uint16_t y);
#endif /* CAMERA_H */