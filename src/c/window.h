#pragma once
#include<pebble.h>

void window_update();

/* Used as a window handler .load. Preapares all resources, layers.*/
void window_load(Window *window);

/* Used as a window handler .unload. Destroys all resources, layers.*/
void window_unload(Window *window);

/* Hide/show layers related to displaying date&time window. */
void display_datetime_window(bool show);

/* Set proper image for battery icon based */
void update_battery_icon();

/* Display battery percentage in menubar instead of time */
void show_battery_menubar();

/* Move layer vertically relatively to given unobstructed area of window by given offset. */
void move_layer_vertically(GRect bounds, char offset, Layer *layer);