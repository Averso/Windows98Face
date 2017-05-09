#include <pebble.h>
#include "globals.h"
#include "callbacks.h"
#include "window.h"
#include "time.h"
static bool is_connected = true; //to vibrate once

//BLUETOOTH
void bluetooth_callback(bool connected) { 
 
  if(persist_exists(CONNECTED_KEY))
  {
     is_connected = persist_read_bool(CONNECTED_KEY);
  }
  
   APP_LOG(APP_LOG_LEVEL_DEBUG, "bt callback");
  //show/hide bluetooth icon depending on connection
  #ifdef PBL_COLOR
  if(settings.monochrome_enabled)
    bitmap_layer_set_bitmap(layer_bt, (connected) ? bitmap_bt_on_bw : bitmap_bt_off_bw);
  else
    bitmap_layer_set_bitmap(layer_bt, (connected) ? bitmap_bt_on : bitmap_bt_off);
  #else
  bitmap_layer_set_bitmap(layer_bt, (connected) ? bitmap_bt_on_bw : bitmap_bt_off_bw);
  #endif
  
  //layer_set_hidden(bitmap_layer_get_layer(layer_bt), connected);
  
  
  //vibrate just once based on previous status
  if((is_connected && !connected) & settings.vibe_on_disconnect)
    vibes_double_pulse();
  
  is_connected = connected;
  persist_write_bool(CONNECTED_KEY,is_connected);
  
}

//BATTERY
void battery_callback(BatteryChargeState state)
{
   if(settings.show_datatime_window && !settings.flick_enabled)
   {
     if( state.is_charging)
     {
        text_layer_set_text(layer_menubar_text,"Chrg");    
     }
     else
     {
      // change text in text layer
      static char s_buffer[5];
      snprintf(s_buffer, sizeof(s_buffer), "%d%%", state.charge_percent);  
      text_layer_set_text(layer_menubar_text, s_buffer);    
     }
     
   }
  
  //save battery level
  battery_level = state.charge_percent;
  
  //change trashbin
  battery_update_trashbin();   
  
}

void battery_update_trashbin()
{ 
  //change vaultboy image depending on battery lvl  
  if(battery_level<=100 && battery_level>settings.battery_warning_level)  
  {
   #ifdef PBL_COLOR
   if(settings.monochrome_enabled)
     bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_low_bw : bitmap_battery_high_bw);
   else
     bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_low : bitmap_battery_high);   
   #else
     bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_low_bw : bitmap_battery_high_bw);  
   #endif
  }   
  else    
  {
    #ifdef PBL_COLOR
    if(settings.monochrome_enabled)
      bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_high_bw : bitmap_battery_low_bw);
    else
      bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_high : bitmap_battery_low);
   #else
    bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_high_bw : bitmap_battery_low_bw);
   #endif
    
  }
    
  
  //not sure if necessary
  layer_mark_dirty(bitmap_layer_get_layer(layer_battery));
}



//ACCELEROMETER - FLICK
void show_battery_menubar()
{
  static char s_buffer[5];
  snprintf(s_buffer, sizeof(s_buffer), "%d%%", battery_level);  
  text_layer_set_text(layer_menubar_text, s_buffer);     
}

void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  
 
  APP_LOG(APP_LOG_LEVEL_DEBUG, "do a flick!");
  if(settings.flick_enabled)
  {
    //show window
     APP_LOG(APP_LOG_LEVEL_DEBUG, "show window!!");
    flick_show_window = true;
    show_datatime_window(flick_show_window);
    show_battery_menubar();
    timer = app_timer_register(settings.flick_show_duration*1000, (AppTimerCallback)timer_callback, NULL); 
     
  }
 

}

void timer_callback(void *data) {
     APP_LOG(APP_LOG_LEVEL_DEBUG, "hide window!!");
    flick_show_window = false;
	 show_datatime_window(flick_show_window);
   update_time();
}
