#pragma once
#include <pebble.h>

/* Call proper method based on provided tick_time.
 * Also call for weather update if it corespond with update interval. */
void tick_handler(struct tm *tick_time, TimeUnits units_changed);

/* Fetch current time and update all text leayers related with displaying time.
 * Also update quiet time icon based on it's current status. */
void update_time();

/* Fetch current time and update all text leayers related with displaying date. */
void update_date();
