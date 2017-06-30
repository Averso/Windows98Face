#pragma once
#include <pebble.h>

//BLUETOOTH
void bluetooth_callback(bool connected); 

//BATTERY
void battery_callback(BatteryChargeState state);

void accel_tap_callback(AccelAxisType axis, int32_t direction);


//QUICKVIEW
#if PBL_API_EXISTS(unobstructed_area_service_subscribe)
void unobstructed_will_change_callback(GRect final_unobstructed_screen_area,void *context);
void unobstructed_did_change_callback(void *context);
void unobstructed_change_callback(AnimationProgress progress, void *context);
#endif
