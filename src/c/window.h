#pragma once
#pragma once
#include <pebble.h>

void window_load(Window *window);
void window_unload(Window *window);
void window_update();
void load_resources();
void create_bitmap_layers(GRect bounds);
void reate_text_layers();
void add_layers_to_window(Layer *window_layer);
void set_up_text_layer(TextLayer *layer, GColor background, GColor text_color, 
const char * text,GFont font,GTextAlignment alignment); //set up text layer with givent parameters
void create_text_layers();
void bitmap_layers_turn_on_transparency();
void show_datatime_window(bool hide);
#ifdef PBL_COLOR
void switch_theme(bool monochrome);
#endif