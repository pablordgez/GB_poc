#include "animation.h"

Animation* THIS_ANIMATION;
AnimationRuntimeData* THIS_ANIMATION_RUNTIME_DATA;


void sub_init_animation(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t animation_id) {
    anim->number_of_frames = num_frames;
    anim->frame_duration = frame_dur;
    anim->animation_id = animation_id;
    anim->props = 0;
    anim->cached = 0;
}


void init_animation(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t animation_id) {
    sub_init_animation(anim, num_frames, frame_dur, animation_id);
    anim->metasprite = (void*)0;
}

void init_animation_metasprite(Animation* anim, uint8_t num_frames, uint8_t frame_dur, uint8_t animation_id, uint8_t width, uint8_t height){
    sub_init_animation(anim, num_frames, frame_dur, animation_id);
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

void init_animation_runtime_data(AnimationRuntimeData* anim_data) {
    anim_data->current_frame = 0;
    anim_data->frame_counter = 0;
    anim_data->flipX = 0;
    anim_data->flipY = 0;
}

void load_animation(Animation* anim, uint8_t x, uint8_t y) {
    const AssetEntry* data_entry = &animation_assets[anim->animation_id];
    uint8_t prev_bank = _current_bank;
    SWITCH_ROM(data_entry->bank);
    if(anim->metasprite == (void*)0){
        THIS_ANIMATION_RUNTIME_DATA->sprite_slot = register_space(&sprite_manager, 1);
        if(anim->cached == 0){
            anim->start_tile = register_space(&sprite_tile_manager, anim->number_of_frames);
            set_sprite_data(anim->start_tile, anim->number_of_frames, data_entry->data);
            anim->cached = 1;
        } else{
            anim->cached++;
        }
        set_sprite_tile(THIS_ANIMATION_RUNTIME_DATA->sprite_slot, anim->start_tile);
        move_sprite(THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
    } else{
        THIS_ANIMATION_RUNTIME_DATA->sprite_slot = register_space(&sprite_manager, anim->width * anim->height);
        if(anim->cached == 0){
            anim->start_tile = register_space(&sprite_tile_manager, anim->number_of_frames * anim->width * anim->height);
            set_sprite_data(anim->start_tile, anim->number_of_frames * anim->width * anim->height, data_entry->data);
            anim->cached = 1;
        } else{
            anim->cached++;
        }
        move_metasprite_ex(anim->metasprite, anim->start_tile, 0, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
    }
    SWITCH_ROM(prev_bank);
    
}

void update_animation(void) {
    THIS_ANIMATION_RUNTIME_DATA->frame_counter++;
    if (THIS_ANIMATION_RUNTIME_DATA->frame_counter < THIS_ANIMATION->frame_duration) {
        return;
    }
    THIS_ANIMATION_RUNTIME_DATA->frame_counter = 0;
    if(THIS_ANIMATION_RUNTIME_DATA->current_frame >= THIS_ANIMATION->number_of_frames - 1){
        THIS_ANIMATION_RUNTIME_DATA->current_frame = 0;
    } else{
        THIS_ANIMATION_RUNTIME_DATA->current_frame++;
    }
    set_sprite_tile(THIS_ANIMATION_RUNTIME_DATA->sprite_slot, THIS_ANIMATION->start_tile + THIS_ANIMATION_RUNTIME_DATA->current_frame);
}

void update_animation_metasprite(uint8_t x, uint8_t y){
    THIS_ANIMATION_RUNTIME_DATA->frame_counter++;
    if (THIS_ANIMATION_RUNTIME_DATA->frame_counter < THIS_ANIMATION->frame_duration) {
        return;
    }
    THIS_ANIMATION_RUNTIME_DATA->frame_counter = 0;
    if(THIS_ANIMATION_RUNTIME_DATA->current_frame >= THIS_ANIMATION->number_of_frames - 1){
        THIS_ANIMATION_RUNTIME_DATA->current_frame = 0;
    } else {
        THIS_ANIMATION_RUNTIME_DATA->current_frame++;
    }
    move_metasprite_ex(THIS_ANIMATION->metasprite, THIS_ANIMATION->start_tile + THIS_ANIMATION_RUNTIME_DATA->current_frame * THIS_ANIMATION->width * THIS_ANIMATION->height, THIS_ANIMATION->props, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
}

void move_animation_sprite(uint8_t x, uint8_t y){
    if(THIS_ANIMATION->metasprite == (void*)0){
        move_sprite(THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
    } else {
        if(THIS_ANIMATION_RUNTIME_DATA->flipX && THIS_ANIMATION_RUNTIME_DATA->flipY){
            move_metasprite_flipxy(THIS_ANIMATION->metasprite, THIS_ANIMATION->start_tile + THIS_ANIMATION_RUNTIME_DATA->current_frame * THIS_ANIMATION->width * THIS_ANIMATION->height, THIS_ANIMATION->props, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
        } else if(THIS_ANIMATION_RUNTIME_DATA->flipX){
            move_metasprite_flipx(THIS_ANIMATION->metasprite, THIS_ANIMATION->start_tile + THIS_ANIMATION_RUNTIME_DATA->current_frame * THIS_ANIMATION->width * THIS_ANIMATION->height, THIS_ANIMATION->props, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
        } else if(THIS_ANIMATION_RUNTIME_DATA->flipY){
            move_metasprite_flipy(THIS_ANIMATION->metasprite, THIS_ANIMATION->start_tile + THIS_ANIMATION_RUNTIME_DATA->current_frame * THIS_ANIMATION->width * THIS_ANIMATION->height, THIS_ANIMATION->props, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
        } else{
            move_metasprite_ex(THIS_ANIMATION->metasprite, THIS_ANIMATION->start_tile + THIS_ANIMATION_RUNTIME_DATA->current_frame * THIS_ANIMATION->width * THIS_ANIMATION->height, THIS_ANIMATION->props, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
        }
    }
}

void unload_animation(Animation* anim) {
    if(anim->cached > 0){
            anim->cached--;
        }
    if(anim->metasprite != (void*)0){
        
        remove_spaces(&sprite_manager, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, anim->width * anim->height);
        if(anim->cached == 0){
            remove_spaces(&sprite_tile_manager, anim->start_tile, anim->number_of_frames * anim->width * anim->height);
        }
    } else{
        remove_spaces(&sprite_manager, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, 1);
        if(anim->cached == 0){
            remove_spaces(&sprite_tile_manager, anim->start_tile, anim->number_of_frames);
        }
    }
}

void change_animation_props(uint8_t props){
    set_sprite_prop(THIS_ANIMATION_RUNTIME_DATA->sprite_slot, props);
    THIS_ANIMATION->props = props;
}

void change_animation_props_metasprite(uint8_t props, uint8_t x, uint8_t y){
    move_metasprite_ex(THIS_ANIMATION->metasprite, THIS_ANIMATION->start_tile + THIS_ANIMATION_RUNTIME_DATA->current_frame * THIS_ANIMATION->width * THIS_ANIMATION->height, props, THIS_ANIMATION_RUNTIME_DATA->sprite_slot, x, y);
    THIS_ANIMATION->props = props;
}

void flip_animation_metasprite(uint8_t flip_x, uint8_t flip_y){
    THIS_ANIMATION_RUNTIME_DATA->flipX = flip_x;
    THIS_ANIMATION_RUNTIME_DATA->flipY = flip_y;
}


void hide_animation(void){
    if(THIS_ANIMATION->metasprite == (void*)0){
        hide_sprite(THIS_ANIMATION_RUNTIME_DATA->sprite_slot);
    } else{
        hide_metasprite(THIS_ANIMATION->metasprite, THIS_ANIMATION_RUNTIME_DATA->sprite_slot);
    }
}

uint8_t get_half_width(void){
    if(THIS_ANIMATION->metasprite == (void*)0){
        return 8; // Standard sprite width is 8 pixels
    } else {
        return (THIS_ANIMATION->width * 8) >> 1;
    }
}

uint8_t get_half_height(void){
    if(THIS_ANIMATION->metasprite == (void*)0){
        return 8; // Standard sprite height is 8 pixels
    } else {
        return (THIS_ANIMATION->height * 8) >> 1;
    }
}