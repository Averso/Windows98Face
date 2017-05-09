#pragma once
#include <pebble.h>

// Persistent storage key
#define SETTINGS_KEY 72631


void inbox_received_handler(DictionaryIterator *iter, void *context);
void load_default_settings();
void save_settings();
void load_settings();
