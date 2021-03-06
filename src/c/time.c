#include <pebble.h>
#include "time.h"
#include "globals.h"

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
    if(units_changed & MINUTE_UNIT)
        update_time();
    if(units_changed & DAY_UNIT)
        update_date(); 
  
 
    if(tick_time->tm_min % settings.weather_update_interval == 0) 
    {    
        DictionaryIterator *iter;
        app_message_outbox_begin(&iter);    
        dict_write_uint8(iter, 0, 0);    
        app_message_outbox_send();
    }
}


void update_time()
{
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);   

    static char time_buff[9];
    static char time_menubar_buff[9];  
  
    strftime(time_buff,sizeof(time_buff), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
    strftime(time_menubar_buff,sizeof(time_menubar_buff), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time); 
  
    text_layer_set_text(textlayer_time, time_buff);
  
    //if flick is enabled, but currently dt widnow is not visible
    //set time text in menubar
    if(!flick_show_dt_window)
        text_layer_set_text(textlayer_menubar, time_menubar_buff);  
  
    //change qt icon depending on status - only on basal/diorite as aplide doesnt support quiettime
    #if defined(PBL_PLATFORM_BASALT) || defined(PBL_PLATFORM_DIORITE)
    bitmap_layer_set_bitmap(bitmaplayer_qt, quiet_time_is_active() ? bitmap_qt[0] : bitmap_qt[1]);  
    #endif
}


void update_date()
{
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);
  
    static char date_buff[11];
    static char month_buff[4];
    static char year_buff[5];
    strftime(date_buff, sizeof(date_buff), "%d", tick_time);
    strftime(month_buff, sizeof(month_buff), "%b", tick_time);
    strftime(year_buff, sizeof(year_buff), "%Y", tick_time);
  
    text_layer_set_text(textlayer_date, date_buff);
    text_layer_set_text(textlayer_month, month_buff);
    text_layer_set_text(textlayer_year, year_buff);
 
}