#include <pebble.h>
#include "callbacks.h"
#include "globals.h"
#include "time.h"
#include "window.h"
#include "settings.h"


static void timer_callback(void *data);

//QUICKVIEW
#if PBL_API_EXISTS(unobstructed_area_service_subscribe)
void unobstructed_will_change_callback(GRect final_unobstructed_screen_area,void *context)
{
  GRect window_full_bounds = layer_get_bounds(window_layer);
  if (!grect_equal(&window_full_bounds, &final_unobstructed_screen_area)) {       
    // move date&time window to new position
    layer_set_frame(bitmap_layer_get_layer(bitmaplayer_datetime_window),GRect(DT_WINDOW_X,0,DT_WINDOW_W,DT_WINDOW_H));    
    layer_set_frame(text_layer_get_layer(textlayer_time),GRect(TIME_DATETIME_X,TIME_DATETIME_Y-DT_WINDOW_Y,TIME_DATETIME_W,TIME_DATETIME_H));    
    layer_set_frame(text_layer_get_layer(textlayer_date),GRect(DATE_DATETIME_X,DATE_DATETIME_Y-DT_WINDOW_Y,DATE_DATETIME_W,DATE_DATETIME_H));
  }
}

void unobstructed_did_change_callback(void *context)
{
  GRect bounds = layer_get_unobstructed_bounds(window_layer);
  GRect window_full_bounds = layer_get_bounds(window_layer);
  if (grect_equal(&window_full_bounds, &bounds)) {    
    //set dt window and its content to original position
   layer_set_frame(bitmap_layer_get_layer(bitmaplayer_datetime_window),GRect(DT_WINDOW_X,DT_WINDOW_Y,DT_WINDOW_W,DT_WINDOW_H));    
   layer_set_frame(text_layer_get_layer(textlayer_time),GRect(TIME_DATETIME_X,TIME_DATETIME_Y,TIME_DATETIME_W,TIME_DATETIME_H));    
   layer_set_frame(text_layer_get_layer(textlayer_date),GRect(DATE_DATETIME_X,DATE_DATETIME_Y,DATE_DATETIME_W,DATE_DATETIME_H));
  }
}

void unobstructed_change_callback(AnimationProgress progress, void *context)
{
  // Get the total available screen real-estate
  GRect bounds = layer_get_unobstructed_bounds(window_layer);
  GRect window_full_bounds = layer_get_bounds(window_layer);
  char window_full_height = window_full_bounds.size.h;  
  
  //move menubar
  move_layer_vertically(bounds, window_full_height - MENUBAR_Y, bitmap_layer_get_layer(bitmaplayer_menubar)); 
  //menubar text
  move_layer_vertically(bounds,window_full_height - TIME_MENUBAR_Y, text_layer_get_layer(textlayer_menubar)); 
  //Same for bluetooth icon
  move_layer_vertically(bounds,window_full_height - MB_ICON_Y, bitmap_layer_get_layer(bitmaplayer_bt)); 
  //Quiettime icon
  move_layer_vertically(bounds,window_full_height - MB_ICON_Y, bitmap_layer_get_layer(bitmaplayer_qt)); 
  //battery icon
  move_layer_vertically(bounds,window_full_height - BATTERY_ICON_Y, bitmap_layer_get_layer(bitmaplayer_battery)); 
  //battery text
  move_layer_vertically(bounds,window_full_height - BATTERY_ICON_TEXT_Y, text_layer_get_layer(textlayer_battery));   
  //desktop icons & texts
  move_layer_vertically(bounds,window_full_height - ICONS_TEXTS_Y,  bitmap_layer_get_layer(bitmaplayer_desktop_text));   
  move_layer_vertically(bounds,window_full_height - ICONS_Y, bitmap_layer_get_layer(bitmaplayer_desktop_icons));   
}
#endif

//BATTERY
void battery_callback(BatteryChargeState state)
{
   if(settings.battery_mode) //baterry icon
   {
      if(state.is_charging)
      {
          text_layer_set_text(textlayer_battery,"Charging");    
      }
      else
      {
          // change text in text layer
          static char s_buffer[9];
          snprintf(s_buffer, sizeof(s_buffer), "%d.pct", state.charge_percent);  
          text_layer_set_text(textlayer_battery, s_buffer);    
      }
   }
  
  //save battery level
  battery_level = state.charge_percent;
  
  //change trashbin
  update_battery_icon();   
}


//BLUETOOTH
void bluetooth_callback(bool connected)
{
  //read connection state from persisten storage
  if(persist_exists(CONNECTED_KEY))  
     is_connected = persist_read_bool(CONNECTED_KEY);
  
  //show/hide bluetooth icon depending on connection
  bitmap_layer_set_bitmap(bitmaplayer_bt, (connected) ? bitmap_bt[0] : bitmap_bt[1]);
  
  //vibrate (just once) basing on previous status
  if((is_connected && !connected) & settings.vibe_on_disconnect)
    vibes_double_pulse();
  
  //save new status to persistent storage
  is_connected = connected;
  persist_write_bool(CONNECTED_KEY,is_connected);
  
}


//ACCELEROMETER - FLICK
void accel_tap_callback(AccelAxisType axis, int32_t direction)
{   
   //show window
   flick_show_dt_window = true;
   display_datetime_window(flick_show_dt_window);
   show_battery_menubar();
   //start timer
   timer = app_timer_register(settings.flick_display_duration*1000, (AppTimerCallback)timer_callback, NULL);        
 
}

static void timer_callback(void *data) {
   //hide window
   flick_show_dt_window = false;
	 display_datetime_window(flick_show_dt_window);
   update_time();
}


//APPMESSAGES
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
    settings.flick_display_duration = flick_display_duration_t->value->uint8;    
  
  
  //battery mode
  Tuple *battery_mode_t = dict_find(iter, MESSAGE_KEY_battery_mode);  
  if(battery_mode_t) 
    settings.battery_mode = battery_mode_t->value->int32 == 1;
 
  
  //battery warning level  
  Tuple *battery_warning_lvl_t = dict_find(iter, MESSAGE_KEY_battery_warning_level);  
  if(battery_warning_lvl_t) 
    settings.battery_warning_level = battery_warning_lvl_t->value->uint8;    
    
  
  //switch bin state
  Tuple *switch_bin_t = dict_find(iter, MESSAGE_KEY_switch_bin_state);
  if(switch_bin_t)
   settings.switch_bin_state = switch_bin_t->value->int32 == 1;
  
  
  //weather enabled
  Tuple *weather_enabled_t = dict_find(iter, MESSAGE_KEY_weather_enabled);
  if(weather_enabled_t)
   settings.weather_enabled = weather_enabled_t->value->int32 == 1;
  
  //weather update interval
  Tuple *weather_update_interval_t = dict_find(iter, MESSAGE_KEY_weather_update_interval);  
  if(weather_update_interval_t) 
    settings.weather_update_interval = weather_update_interval_t->value->uint8; 
  
   
  //save loaded settings
  save_settings();
  
  
  //WEATHER
  static char temperature_buffer[8];
  Tuple *temp_tuple = dict_find(iter, MESSAGE_KEY_weather_temperature);
  Tuple *icon_tuple = dict_find(iter, MESSAGE_KEY_weather_icon);
  if(temp_tuple && icon_tuple) {
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", temp_tuple->value->cstring);
    updateWeatherTextIcon(temperature_buffer,icon_tuple->value->uint8);
  }
    
  
}

