#include <pebble.h>
#include "settings.h"
#include "globals.h"
#include "window.h"


/* Set default settings. */
static void load_default_settings();

/* Write settings to persistent storag. */
static void save_settings();


static void load_default_settings()
{  
  #ifdef PBL_COLOR
  settings.color_background = GColorTiffanyBlue;
  settings.color_text = GColorWhite;
  #endif
  
  #ifdef PBL_BW
  settings.color_background = true;
  #endif  
  
  settings.vibe_on_disconnect = true;
  settings.date_format = false; 
  settings.flick_display_duration = 10;  
  settings.battery_mode = false; //false = Recycle Bin
  settings.battery_warning_level = BATTERY_DEFAULT_WARNING_LVL;
  settings.switch_bin_state = false;
  settings.weather_enabled=true;
  settings.weather_unit=true; //false - fahrenheit
  settings.weather_gps_on=false; 
  settings.weather_interval=30;

}

static void save_settings()
{
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));    
  
  //refresh window 
  window_update();
}

void load_settings()
{
  // Load the default settings
  load_default_settings();
  
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void inbox_received_handler(DictionaryIterator *iter, void *context)
{
 
  #ifdef PBL_COLOR  
  //background color
  Tuple *color_background_t = dict_find(iter, MESSAGE_KEY_color_background);
  if(color_background_t)
    settings.color_background = GColorFromHEX(color_background_t->value->int32);
  
  //text color
  Tuple *color_text_t = dict_find(iter, MESSAGE_KEY_color_text);
  if(color_text_t)
    settings.color_text = GColorFromHEX(color_text_t->value->int32); 
  #endif
  
  #ifdef PBL_BW
  //background color
  Tuple *color_background_t = dict_find(iter, MESSAGE_KEY_color_background_bw);
  if(color_background_t) 
   settings.color_background = color_background_t->value->int32 == 1;
   
  #endif
  
  //disconnect vibration
  Tuple *vibe_on_disconnect_t = dict_find(iter, MESSAGE_KEY_vibe_on_disconnect);
  if(vibe_on_disconnect_t) 
   settings.vibe_on_disconnect = vibe_on_disconnect_t->value->int32 == 1;
  
  //date format
  Tuple *date_format_t = dict_find(iter, MESSAGE_KEY_date_format);
  if(date_format_t) 
   settings.date_format = date_format_t->value->int32 == 1;
 
  //flick display duration
  Tuple *flick_display_duration_t = dict_find(iter, MESSAGE_KEY_flick_display_duration);  
  if(flick_display_duration_t) 
    settings.flick_display_duration = atoi(flick_display_duration_t->value->cstring);    
  
  
  //battery mode
  Tuple *battery_mode_t = dict_find(iter, MESSAGE_KEY_battery_mode);  
  if(battery_mode_t) 
    settings.battery_mode = battery_mode_t->value->int32 == 1;
 
  
  //battery warning level  
  Tuple *battery_warning_lvl_t = dict_find(iter, MESSAGE_KEY_battery_warning_level);  
  if(battery_warning_lvl_t) 
    settings.battery_warning_level = atoi(battery_warning_lvl_t->value->cstring);    
    
  
  //switch bin state
  Tuple *switch_bin_t = dict_find(iter, MESSAGE_KEY_switch_bin_state);
  if(switch_bin_t)
   settings.switch_bin_state = switch_bin_t->value->int32 == 1;
  
  
  //save loaded settings
  save_settings();
  
  
}

