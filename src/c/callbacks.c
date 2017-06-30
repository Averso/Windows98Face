#include <pebble.h>
#include "callbacks.h"
#include "globals.h"
#include "time.h"
#include "window.h"

static void timer_callback(void *data);


//QUICKVIEW
#if PBL_API_EXISTS(unobstructed_area_service_subscribe)
void unobstructed_will_change_callback(GRect final_unobstructed_screen_area,void *context)
{
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
   flick_show_dt_window = false;
   display_datetime_window(flick_show_dt_window);
   show_battery_menubar();
   //start timer
   timer = app_timer_register(settings.flick_display_duration*1000, (AppTimerCallback)timer_callback, NULL);        
 
}

static void timer_callback(void *data) {
   //hide window
   flick_show_dt_window = true;
	 display_datetime_window(flick_show_dt_window);
   update_time();
}
