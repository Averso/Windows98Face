#include <pebble.h>
#include "globals.h"
#include "settings.h"
#include "window.h"


void save_settings() { 
//    APP_LOG(APP_LOG_LEVEL_DEBUG, "save settings");
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));  
  
  //refresh window 
  window_update();
}

void load_default_settings() {  
  
//    APP_LOG(APP_LOG_LEVEL_DEBUG, "load default settings");
  settings.window_x = WINDOW_X;
  settings.window_y = WINDOW_Y;
  settings.battery_warning_level = BETTERY_DEFAULT_LVL;
  settings.vibe_on_disconnect = false;  
  settings.show_datatime_window = false;
  settings.center_pos = false;
  settings.switch_bin_state = false;
  settings.date_format = false;
  settings.flick_enabled = false;
  settings.flick_show_duration = 10;
  settings.weather_enabled = false;
  settings.temperature_format = false;
  settings.weather_api_key = "1111111111";
  
  #ifdef PBL_COLOR  
  settings.bg_color = GColorTiffanyBlue;
  settings.text_color = GColorWhite;
  settings.monochrome_enabled = false;
  #endif
  
  #ifdef PBL_BW
  settings.bg_color = false;
  #endif
}

void inbox_received_handler(DictionaryIterator *iter, void *context) {
//    APP_LOG(APP_LOG_LEVEL_DEBUG, "read settings");
  
  
  //assign the values from settings to struct
  //vibration on disconnect
  Tuple *vibe_enabled = dict_find(iter, MESSAGE_KEY_vibe_disconnect);
  if(vibe_enabled) {
   settings.vibe_on_disconnect = vibe_enabled->value->int32 == 1;
  }   
  
  //battery warning level  
  Tuple *bat_warning_lvl = dict_find(iter, MESSAGE_KEY_battery_warning_level);  
  if(bat_warning_lvl) {
    settings.battery_warning_level = atoi(bat_warning_lvl->value->cstring);    
  }  
  
  //switch bin
  Tuple *switch_bin_t = dict_find(iter, MESSAGE_KEY_switch_bin_state);
  if(switch_bin_t) {
   settings.switch_bin_state = switch_bin_t->value->int32 == 1;
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
  
  //date format
  Tuple *date_format_t = dict_find(iter, MESSAGE_KEY_date_format);
  if(date_format_t) {
   settings.date_format = date_format_t->value->int32 == 1;
  }  
  
  //enable flick
  Tuple *enable_flick_t = dict_find(iter, MESSAGE_KEY_enable_flick);
  if(enable_flick_t) {
   settings.flick_enabled = enable_flick_t->value->int32 == 1;
  }
  
  //show window time duration
  Tuple *show_duration_t = dict_find(iter, MESSAGE_KEY_flick_show_duration);  
  if(window_y) {
    settings.flick_show_duration = atoi(show_duration_t->value->cstring);    
  }

  //enable weather
  Tuple *enable_weather_t = dict_find(iter, MESSAGE_KEY_enable_weather);
  if (enable_weather_t) {
    settings.weather_enabled = enable_weather_t->value->int32 == 1;
  }

  //get the temperature
  Tuple *temperature_t = dict_find(iter, MESSAGE_KEY_temperature);
  temperature = (int)temperature_t->value->int32;

  //toggle between faherenheit and celsius
  Tuple *temperature_format_t = dict_find(iter, MESSAGE_KEY_temperature_format);
  if (temperature_format_t) {
    settings.temperature_format = temperature_format_t->value->int32 == 1;
  }

  //get weather api key
  Tuple *weather_api_key_t = dict_find(iter, MESSAGE_KEY_weather_api_key);  
  if(weather_api_key_t) {
    settings.weather_api_key = weather_api_key_t->value->cstring;    
  }    
   
  #ifdef PBL_COLOR
   //bg color
  Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_bg_color);
  if(bg_color_t) {
    settings.bg_color = GColorFromHEX(bg_color_t->value->int32);
  }

  //text color
  Tuple *text_color_t = dict_find(iter, MESSAGE_KEY_text_color);
  if(text_color_t) {
    settings.text_color = GColorFromHEX(text_color_t->value->int32);
  }
  
  //monochrome 
  Tuple *mono_t = dict_find(iter, MESSAGE_KEY_monochrome_enabled);
  if(mono_t) {
   settings.monochrome_enabled = mono_t->value->int32 == 1;
  }  
  
  #endif
  
  
  #ifdef PBL_BW
  Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_bg_color_bw);
  if(bg_color_t) {
   settings.bg_color = bg_color_t->value->int32 == 1;
  }  
  #endif
  
  //manage flick and windows settings
   
  //if data time window is disables - disable flick
  if(!settings.show_datatime_window)
  {
    settings.flick_enabled = false;
  }
  
  //if flick is enables - hide window as it will show after flicks
  if(settings.flick_enabled)
  {
    flick_show_window = false;
  }
  
  
  //save loaded settings
  save_settings();
  
  
    
}

void load_settings() {
  
//    APP_LOG(APP_LOG_LEVEL_DEBUG, "load settings");
  // Load the default settings
  load_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}


