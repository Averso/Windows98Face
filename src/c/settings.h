#pragma once
#include <pebble.h>


/* Handle AppMessage conetion messages. Assign the values from clay settings to settings struct. */
void inbox_received_handler(DictionaryIterator *iter, void *context);

/* Load default settings and read settings from persistent storage if exist. */
void load_settings();
