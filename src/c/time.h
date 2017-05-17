#pragma once
#include <pebble.h>

//handle fetching time/date data
void tick_handler(struct tm *tick_time, TimeUnits units_changed);

//update time text layers and quiet time status icons
void update_time();  

//update date text layers
void update_date();


//void update_all();