#pragma once
#include <pebble.h>

/* Load default settings and after that read settings from persistent storage if they exist. */
void load_settings();

/* Write settings to persistent storage and call for refresh of the window. */
void save_settings();