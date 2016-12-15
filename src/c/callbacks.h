#pragma once

 
void bluetooth_callback(bool connected); 
void battery_callback(BatteryChargeState state);
void battery_update_trashbin();