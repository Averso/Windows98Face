#pragma once
#include<pebble.h>

/* Used for updating windows elements withour initializing everything from scratch.
 * Updates window elements with data provided from settings, calls for bluetooth, battery, time status refresh.*/
void window_update();

/* Initialize all resources&layers.*/
void window_load(Window *window);

/* Destroy all resources&layers.*/
void window_unload(Window *window);

/* Hide/show layers related to date&time window. */
void display_datetime_window(bool show);

/* Set proper image for battery icon based on battery status. */
void update_battery_icon();

/* Display battery percentage in menubar instead of time.*/
void show_battery_menubar();

/* Move layer vertically relatively to given unobstructed area of window by given offset. */
void move_layer_vertically(GRect bounds, char offset, Layer *layer);

/* Update weather text with given temerature and set icon appropriate to provided weather conditions*/
void update_weather_text_icon(const char * temp, uint8_t icon_num);
