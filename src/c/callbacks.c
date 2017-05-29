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
  
   
  //show/hide bluetooth icon depending on connection
  bitmap_layer_set_bitmap(layer_bt, (connected) ? bitmap_bt_on : bitmap_bt_off);
 
  //vibrate (just once) basing on previous status
  if((is_connected && !connected) & settings.vibe_on_disconnect)
    vibes_double_pulse();
  
  is_connected = connected;
  persist_write_bool(CONNECTED_KEY,is_connected);
  
}

//BATTERY
void battery_callback(BatteryChargeState state)
{
  
   if(settings.battery_mode) //baterry icon
   {
      if( state.is_charging)
      {
          text_layer_set_text(layer_battery_text,"Charging");    
      }
      else
      {
          // change text in text layer
          static char s_buffer[9];
          snprintf(s_buffer, sizeof(s_buffer), "%d.pct", state.charge_percent);  
          text_layer_set_text(layer_battery_text, s_buffer);    
      }
   }
   else //recycle bin
   {
      //switch icon text to default 'recycle bin' (however maybe it should be put somewhere else to decrease calls for set text)
      text_layer_set_text(layer_battery_text, "Recycle Bin");
      // if we check time/date, show battery status in menubar 
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
   }
  
   
   
  
  //save battery level
  battery_level = state.charge_percent;
  
  //change trashbin
  battery_update_icon();   
  
}

void battery_update_icon()
{ 
  if(settings.battery_mode) //baterry icon
  {
    //change battery image depending on battery lvl  
    if(battery_level<=100 && battery_level>50)      
      bitmap_layer_set_bitmap(layer_battery, bitmap_battery_icon[0]);    
    else if (battery_level<=50 && battery_level>25)    
     bitmap_layer_set_bitmap(layer_battery, bitmap_battery_icon[1]);    
    else if (battery_level<=25 && battery_level>10)
      bitmap_layer_set_bitmap(layer_battery, bitmap_battery_icon[2]);
    else
      bitmap_layer_set_bitmap(layer_battery, bitmap_battery_icon[3]);
  
  }
  else //recycle bin
  {
    //change recycle bin image depending on battery lvl  
    if(battery_level<=100 && battery_level>settings.battery_warning_level)  
       bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_low : bitmap_battery_high);     
    else     
      bitmap_layer_set_bitmap(layer_battery, settings.switch_bin_state ? bitmap_battery_high : bitmap_battery_low);
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
  
  if(settings.flick_enabled)
  {
    //show window
    flick_show_window = true;
    show_datatime_window(flick_show_window);
    show_battery_menubar();
    //start timer
    timer = app_timer_register(settings.flick_show_duration*1000, (AppTimerCallback)timer_callback, NULL);      
  }
 

}

void timer_callback(void *data) {
   //hide window
   flick_show_window = false;
	 show_datatime_window(flick_show_window);
   update_time();
}
