#include "animation.h"
void init_animation(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t sprite_id, SpaceManager* sprite_manager, SpaceManager* tile_manager) {
    anim->number_of_frames = num_frames;
    anim->frame_duration = frame_dur;
    anim->sprite_id = sprite_id;
    anim->sprite_slot = get_free_space(sprite_manager, 1);
    register_space_no_data(sprite_manager, 1);
    anim->start_tile = get_free_space(tile_manager, num_frames);
    register_space_no_data(tile_manager, num_frames);
    anim->current_frame = 0;
    anim->frame_counter = 0;
    anim->metasprite = (void*)0;
}

void init_animation_metasprite(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t sprite_id, uint8_t width, uint8_t height, SpaceManager* sprite_manager, SpaceManager* tile_manager){
    anim->number_of_frames = num_frames;
    anim->frame_duration = frame_dur;
    anim->sprite_id = sprite_id;
    anim->sprite_slot = get_free_space(sprite_manager, width * height);
    register_space_no_data(sprite_manager, width * height);
    anim->start_tile = get_free_space(tile_manager, num_frames * width * height);
    register_space_no_data(tile_manager, num_frames * width * height);
    anim->current_frame = 0;
    anim->frame_counter = 0;
    anim->width = width;
    anim->height = height;
    metasprite_t* anim_metasprite = malloc(sizeof(metasprite_t) * (anim->width * anim->height + 1));
    if(anim_metasprite == (void*)0) {
        return; // Memory allocation failed
    }
    int8_t pivotY = -8 * (anim->height / 2);
    int8_t pivotX = -8 * (anim->width / 2);
    for(uint8_t i = 0; i < anim->height; i++){
        for(uint8_t j = 0; j < anim->width; j++){
            anim_metasprite[i * anim->width + j].dy = pivotY;
            anim_metasprite[i * anim->width + j].dx = pivotX;
            pivotY = 0;
            pivotX = 8;
            anim_metasprite[i * anim->width + j].dtile = anim->start_tile + (i * anim->width + j);
            anim_metasprite[i * anim->width + j].props = 0;
        }
        pivotY = 8;
        pivotX = -8 * (anim->width / 2);
    }
    anim_metasprite[anim->width * anim->height].dy = metasprite_end;
    anim_metasprite[anim->width * anim->height].dx = 0;
    anim_metasprite[anim->width * anim->height].dtile = 0;
    anim_metasprite[anim->width * anim->height].props = 0;
    anim->metasprite = anim_metasprite;
}

void load_animation(Animation* anim, uint8_t x, uint8_t y) {
    const AssetEntry* data_entry = &sprites[anim->sprite_id];
    uint8_t prev_bank = _current_bank;
    SWITCH_ROM(data_entry->bank);
    if(anim->metasprite == (void*)0){
        set_sprite_data(anim->start_tile, anim->number_of_frames, data_entry->data);
        set_sprite_tile(anim->sprite_slot, anim->start_tile);
        move_sprite(anim->sprite_slot, x, y);
    } else{
        set_sprite_data(anim->start_tile, anim->number_of_frames * anim->width * anim->height, data_entry->data);
        move_metasprite_ex(anim->metasprite, anim->start_tile, 0, anim->sprite_slot, x, y);
    }
    SWITCH_ROM(prev_bank);
    
}

void update_animation(Animation* anim) {
    anim->frame_counter++;
    if (anim->frame_counter < anim->frame_duration) {
        return;
    }
    anim->frame_counter = 0;
    if(anim->current_frame >= anim->number_of_frames - 1){
        anim->current_frame = 0;
    } else{
        anim->current_frame++;
    }
    set_sprite_tile(anim->sprite_slot, anim->start_tile + anim->current_frame);
}

void update_animation_metasprite(Animation* anim, uint8_t x, uint8_t y){
    anim->frame_counter++;
    if (anim->frame_counter < anim->frame_duration) {
        return;
    }
    anim->frame_counter = 0;
    if(anim->current_frame >= anim->number_of_frames - 1){
        anim->current_frame = 0;
    } else {
        anim->current_frame++;
    }
    move_metasprite_ex(anim->metasprite, anim->start_tile + anim->current_frame * anim->width * anim->height, 0, anim->sprite_slot, x, y);
}

void move_animation_sprite(Animation* anim, uint8_t x, uint8_t y){
    if(anim->metasprite == (void*)0){
        move_sprite(anim->sprite_slot, x, y);
    } else {
        move_metasprite_ex(anim->metasprite, anim->start_tile + anim->current_frame * anim->width * anim->height, 0, anim->sprite_slot, x, y);
    }
}