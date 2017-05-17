#pragma once

 
void bluetooth_callback(bool connected); 
void battery_callback(BatteryChargeState state);
void battery_update_icon();
void timer_callback(void *data);
void show_battery_menubar();
void accel_tap_handler(AccelAxisType axis, int32_t direction);