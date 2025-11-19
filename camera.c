#include "camera.h"

uint8_t camera_x = 0;
uint8_t camera_y = 0;
uint8_t limit_x = 140;
uint8_t limit_y = 124;
uint8_t max_cam_x = 96;
uint8_t max_cam_y = 112;                                                                                                                                                                                                                                                                                                                                                        

void update_camera(uint16_t x, uint16_t y) {
    uint8_t draw_x = (x >> 4) - camera_x;
    uint8_t draw_y = (y >> 4) - camera_y;
    
    if(draw_x > limit_x){
        camera_x = (x >> 4) - limit_x;
    }
    else if(draw_x < 160 - limit_x && camera_x > 0){
        camera_x = (x >> 4) - (160 - limit_x);
    }
    if(draw_y > limit_y){
        camera_y = (y >> 4) - limit_y;
    }
    else if(draw_y < 144 - limit_y && camera_y > 0){
        camera_y = (y >> 4) - (144 - limit_y);
    }
    if(camera_x > max_cam_x){
        camera_x = max_cam_x;
    }
    if(camera_y > max_cam_y){
        camera_y = max_cam_y;
    }
    if(in_debug == 0){
        move_bkg(camera_x, camera_y);
    }
    
}