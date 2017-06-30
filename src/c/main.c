#include <pebble.h>
#include "globals.h"
#include "window.h"
#include "time.h"
#include "callbacks.h"
#include "settings.h"


static void init(void);
static void deinit(void);


int main(void)
{
  init();
  app_event_loop();
  deinit();
}

static void init(void)
{
  //VARIABLES INIT
  flick_show_dt_window = false;  
  is_connected = true;
  
  main_window = window_create();
  
  if(main_window)
  { 
    APP_LOG(APP_LOG_LEVEL_DEBUG, "used %zu; free: %zu",heap_bytes_used(),heap_bytes_free());
    //Load settings
    load_settings();
    
    //open AppMessage
    app_message_register_inbox_received(inbox_received_handler);
    app_message_open(128, 128);
    
    //WINDOW      
    window_set_window_handlers(main_window,(WindowHandlers){
         .load = window_load,
         .unload = window_unload
    });
    
    window_stack_push(main_window,true);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "used %zu; free: %zu",heap_bytes_used(),heap_bytes_free());
    
    //UnobstructedArea
    #if PBL_API_EXISTS(unobstructed_area_service_subscribe)
     UnobstructedAreaHandlers handlers = {
      .will_change = unobstructed_will_change_callback,
      .change = unobstructed_change_callback,
      .did_change = unobstructed_did_change_callback
    };
    unobstructed_area_service_subscribe(handlers, NULL);
    #endif
    APP_LOG(APP_LOG_LEVEL_DEBUG, "used %zu; free: %zu",heap_bytes_used(),heap_bytes_free());
    //TAP EVENTS
    accel_tap_service_subscribe(accel_tap_callback); 
        
    //BATTERY
    battery_state_service_subscribe(battery_callback); 
    
    //BLUETOOTH
    connection_service_subscribe((ConnectionHandlers){
      .pebble_app_connection_handler = bluetooth_callback
    });
    
    //TIMER
    tick_timer_service_subscribe(MINUTE_UNIT | DAY_UNIT, tick_handler);
    
    //GET STATES
    
  }
}

static void deinit(void)
{
  if(main_window)
  {
     window_destroy(main_window);
      
     
     tick_timer_service_unsubscribe();
     connection_service_unsubscribe();
     battery_state_service_unsubscribe();
     accel_tap_service_unsubscribe();  
     unobstructed_area_service_unsubscribe();
  }
 
}
