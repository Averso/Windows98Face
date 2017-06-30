#pragma once
#include <pebble.h>

void tick_handler(struct tm *tick_time, TimeUnits units_changed);
void update_time();
void update_date();
