#pragma once
#include <pebble.h>

/* Load default settings and read settings from persistent storage if exist. */
void load_settings();

/* Write settings to persistent storag. */
void save_settings();