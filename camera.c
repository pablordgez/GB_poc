#include "camera.h"


uint16_t camera_x = 0;
uint16_t camera_y = 0;
uint16_t old_camera_x = 0;
uint16_t old_camera_y = 0;
uint8_t limit_x = 140;
uint8_t limit_y = 124;
uint16_t max_cam_x = 0;
uint16_t max_cam_y = 0;
Map* active_map = NULL;

void set_active_map(Map* map) {
    max_cam_x = (map->width << 3) - SCREEN_WIDTH;
    max_cam_y = (map->height << 3) - SCREEN_HEIGHT;
    active_map = map;
}

void update_camera(uint16_t x, uint16_t y) {
    uint16_t target_x = x >> 4;
    uint16_t target_y = y >> 4;
    uint8_t draw_x = target_x - camera_x;
    uint8_t draw_y = target_y - camera_y;
    
    if(draw_x > limit_x){
        camera_x = target_x - limit_x;
    }
    else if(draw_x < SCREEN_WIDTH - limit_x && camera_x > 0){
        camera_x = target_x - (SCREEN_WIDTH - limit_x);
    }
    if(draw_y > limit_y){
        camera_y = target_y - limit_y;
    }
    else if(draw_y < SCREEN_HEIGHT - limit_y && camera_y > 0){
        camera_y = target_y - (SCREEN_HEIGHT - limit_y);
    }
    if(camera_x > max_cam_x){
        camera_x = max_cam_x;
    }
    if(camera_y > max_cam_y){
        camera_y = max_cam_y;
    }


    if((camera_x >> 3) != (old_camera_x >> 3)){
        if(camera_x > old_camera_x){
            uint8_t col = (camera_x + SCREEN_WIDTH) >> 3;
            set_bkg_submap(col, camera_y >> 3, 1, 19, active_map->map_data, active_map->width);
        } else{
            uint8_t col = camera_x >> 3;
            set_bkg_submap(col, camera_y >> 3, 1, 19, active_map->map_data, active_map->width);
        }
    }

    if((camera_y >> 3) != (old_camera_y >> 3)){
        if(camera_y > old_camera_y){
            uint8_t row = (camera_y + SCREEN_HEIGHT) >> 3;
            set_bkg_submap(camera_x >> 3, row, 21, 1, active_map->map_data, active_map->width);
        } else{
            uint8_t row = camera_y >> 3;
            set_bkg_submap(camera_x >> 3, row, 21, 1, active_map->map_data, active_map->width);
        }
    }

    if(in_debug == 0){
        move_bkg(camera_x, camera_y);
    }

    old_camera_x = camera_x;
    old_camera_y = camera_y;
    
}