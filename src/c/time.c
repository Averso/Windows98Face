#include <pebble.h>
#include "time.h"
#include "globals.h"

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
  if (units_changed & MINUTE_UNIT)
     update_time();
      
  if(units_changed & DAY_UNIT)  
    if(settings.show_datatime_window)
      update_date();      
  
  
}

void update_time()
{
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char time_buff[9];
  static char time_menubar_buff[9];
  
  strftime(time_buff,sizeof(time_buff), clock_is_24h_style() ?  "%H:%M" : "%I:%M %p", tick_time);   
  strftime(time_menubar_buff, sizeof(time_menubar_buff), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);  
  
  //set time text in data/time window if enabled
  if(settings.show_datatime_window)
  {
    text_layer_set_text(layer_time, time_buff);
    
    //if flick is enabled, but currently dt widnow is not visible
    //set time text in menubar
    if(settings.flick_enabled && !flick_show_window)
      text_layer_set_text(layer_menubar_text, time_menubar_buff);
    
  }
  else //when datatime window id disabled
  {
    text_layer_set_text(layer_menubar_text, time_menubar_buff);
  }


  //change qt icon depending on status
  if(quiet_time_is_active())    
    bitmap_layer_set_bitmap(layer_qt, bitmap_qt_on);  
  else
  {   
    bitmap_layer_set_bitmap(layer_qt, bitmap_qt_off);
  }     
  
}

void update_date() 
{
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char date_buff[11];
  strftime(date_buff, sizeof(date_buff), settings.date_format ?"%m-%d-%Y" : "%d-%m-%Y", tick_time);

  text_layer_set_text(layer_date, date_buff);
}
