#pragma once
#include <pebble.h>

//BLUETOOTH
/* Save current battery level. If we show battery icon insted of Recycle Bin, update battery text
 * layer with current battery status. Call for update of batery bitmap layer.*/
void bluetooth_callback(bool connected); 

/* Save current battery level. If we show battery icon insted of Recycle Bin, update battery text
 * layer with current battery status. Call for update of batery bitmap layer.*/
void battery_callback(BatteryChargeState state);

/* Show data&time window, battery status in menubar and start timer hiding window
 * after time set in settings. */ 
void accel_tap_callback(AccelAxisType axis, int32_t direction);


#if PBL_API_EXISTS(unobstructed_area_service_subscribe)
/* Occurs when quick view is about to show up. It changes position of data&time window and it's content
 to fit in space left after quickview showing up.*/
void unobstructed_will_change_callback(GRect final_unobstructed_screen_area,void *context);

/* Occurs when quick view was closed. We revert position of data&time window and it's content
 to original.*/
void unobstructed_did_change_callback(void *context);

/* Occurs when quick view is rising up/hiding. It updates position of menubar, desktop icons to fit in unobstructed area.*/
void unobstructed_change_callback(AnimationProgress progress, void *context);
#endif


//APPMESSAGES
/* Handler to receive and manage data sent to Pebble with AppMessage Api - which is Clay Settings data
   and weather data. WE*/
void inbox_received_handler(DictionaryIterator *iter, void *context);