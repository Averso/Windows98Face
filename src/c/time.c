#include <pebble.h>
#include "time.h"
#include "globals.h"

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
  if (units_changed & MINUTE_UNIT)
  {
     update_time();
      
  
  }
  if(units_changed & DAY_UNIT)
  {
    if(settings.show_datatime_window)
      update_date();      
  }
  
}


void update_all()
{
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);  
   
  static char time[9];
  
  strftime(time, sizeof(time), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);   
  
  text_layer_set_text(layer_time, time);  
  text_layer_set_text(layer_menubar_text, time);
  
  static char date[11];

  strftime(date, sizeof(date),settings.date_format ?"%m-%d-%Y" : "%d-%m-%Y", tick_time);  
  text_layer_set_text(layer_date, date);
  
}
void update_time()
{
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);  
  
  static char time[9];
  static char time_menubar[9];
  strftime(time, sizeof(time), clock_is_24h_style() ? "%H:%M" : "%I:%M %p", tick_time);    
  strftime(time_menubar, sizeof(time_menubar), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);    
  
  //set text in data/time window when enabled and flcik disabled
  if(settings.show_datatime_window)
  {  
    text_layer_set_text(layer_time, time);    
  }
  

  if(settings.show_datatime_window && (settings.flick_enabled && !flick_show_window))
  {  
    
         text_layer_set_text(layer_menubar_text, time_menubar);    
      
        
  }
  else if (!settings.show_datatime_window)
  {
        text_layer_set_text(layer_menubar_text, time_menubar);
  }


  
  if(quiet_time_is_active())
  {
    #ifdef PBL_COLOR 
    bitmap_layer_set_bitmap(layer_qt,settings.monochrome_enabled ? bitmap_qt_on_bw : bitmap_qt_on);
    #else
    bitmap_layer_set_bitmap(layer_qt, bitmap_qt_on_bw);
    #endif
  }     
  else
  {
    #ifdef PBL_COLOR 
     bitmap_layer_set_bitmap(layer_qt,settings.monochrome_enabled ? bitmap_qt_off_bw : bitmap_qt_off);
    #else
    bitmap_layer_set_bitmap(layer_qt, bitmap_qt_off_bw);
    #endif
  }     
  
}


void update_date() 
{
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char s_buffer[11];
  strftime(s_buffer, sizeof(s_buffer), settings.date_format ?"%m-%d-%Y" : "%d-%m-%Y", tick_time);
  
  text_layer_set_text(layer_date, s_buffer);
}
