#include <pebble.h>
#include "globals.h"
#include "settings.h"
#include "window.h"


void save_settings() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "save settings");
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));  
  //refresh window
  APP_LOG(APP_LOG_LEVEL_DEBUG, "update");
  window_update();
}

void load_default_settings() {  
  settings.window_x = WINDOW_X;
  settings.window_y = WINDOW_Y;
  settings.battery_warning_level = BETTERY_DEFAULT_LVL;
  settings.vibe_on_disconnect = false;
  settings.bg_color = GColorTiffanyBlue;
  settings.show_datatime_window = false;
  settings.center_pos = false;
}

void inbox_received_handler(DictionaryIterator *iter, void *context) {
  
  
  //assign the values from settings to struct
  //vibration on disconnect
  Tuple *vibe_enabled = dict_find(iter, MESSAGE_KEY_vibe_disconnect);
  if(vibe_enabled) {
   settings.vibe_on_disconnect = vibe_enabled->value->int32 == 1;
  }  
  //bg color
  Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_bg_color);
  if(bg_color_t) {
    settings.bg_color = GColorFromHEX(bg_color_t->value->int32);
  }
  
  //battery warning level  
  Tuple *bat_warning_lvl = dict_find(iter, MESSAGE_KEY_battery_warning_level);  
  if(bat_warning_lvl) {
    settings.battery_warning_level = atoi(bat_warning_lvl->value->cstring);    
  }  
  
   //window x 
  Tuple *window_x = dict_find(iter, MESSAGE_KEY_window_x);  
  if(window_x) {
    settings.window_x = atoi(window_x->value->cstring);    
  }      
  
   //window y  
  Tuple *window_y = dict_find(iter, MESSAGE_KEY_window_y);  
  if(window_y) {
    settings.window_y = atoi(window_y->value->cstring);    
  }    
  
  //data time window
  Tuple *window_enabled = dict_find(iter, MESSAGE_KEY_enable_window);
  if(window_enabled) {
   settings.show_datatime_window = window_enabled->value->int32 == 1;
  }  
  
  //datatime window center
  Tuple *center_pos = dict_find(iter, MESSAGE_KEY_center_pos);
  if(center_pos) {
   settings.center_pos = center_pos->value->int32 == 1;
  }  
  
  //if center - change x,y coords
  if(settings.center_pos)
  {
    settings.window_x = WINDOW_CENTER_X;
    settings.window_y = WINDOW_CENTER_Y;
  }
  
  //save loaded settings
  save_settings();
}

void load_settings() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "load defaul");
  // Load the default settings
  load_default_settings();
  // Read settings from persistent storage, if they exist
  APP_LOG(APP_LOG_LEVEL_DEBUG, "read data");
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}


