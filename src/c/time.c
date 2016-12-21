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

  strftime(date, sizeof(date),settings.date_format ?"%m-%d-%G" : "%d-%m-%G", tick_time);  
  text_layer_set_text(layer_date, date);
  
}
void update_time()
{
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);  
  
  static char s_buffer[9];
  
  //if window - show AM or PM designation
  if( settings.show_datatime_window)
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M %p", tick_time);    
  else
    strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);    
  
  if(settings.show_datatime_window)
    text_layer_set_text(layer_time, s_buffer);
  else    
    text_layer_set_text(layer_menubar_text, s_buffer);
  
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
  strftime(s_buffer, sizeof(s_buffer), settings.date_format ?"%m-%d-%G" : "%d-%m-%G", tick_time);
  
  text_layer_set_text(layer_date, s_buffer);
}
