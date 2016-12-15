#include <pebble.h>
#include "globals.h"
#include "callbacks.h"

static bool is_connected = true; //to vibrate once

//BLUETOOTH
void bluetooth_callback(bool connected) { 
 
  if(persist_exists(CONNECTED_KEY))
  {
     is_connected = persist_read_bool(CONNECTED_KEY);
  }
  
  //show/hide bluetooth icon depending on connection
  bitmap_layer_set_bitmap(layer_bt, (connected) ? bitmap_bt_on : bitmap_bt_off);
//   layer_set_hidden(bitmap_layer_get_layer(layer_bt), connected);
  
  
  //vibrate just once based on previous status
  if((is_connected && !connected) & settings.vibe_on_disconnect)
    vibes_double_pulse();
  
  is_connected = connected;
  persist_write_bool(CONNECTED_KEY,is_connected);
  
}

//BATTERY
void battery_callback(BatteryChargeState state)
{
   if(settings.show_datatime_window)
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
    bitmap_layer_set_bitmap(layer_battery, bitmap_battery_high);
  }
  else    
    bitmap_layer_set_bitmap(layer_battery, bitmap_battery_low);
  
  //not sure if necessary
  layer_mark_dirty(bitmap_layer_get_layer(layer_battery));
}

