#include <pebble.h>
#include "settings.h"
#include "globals.h"
#include "window.h"


/* Set default settings. */
static void load_default_settings();


static void load_default_settings()
{    
    LOG_FUNC_START("load_default_settings");
    #ifdef PBL_COLOR
    settings.color_background = GColorTiffanyBlue;
    settings.color_text = GColorWhite;
    #endif
  
    #ifdef PBL_BW
    settings.color_background = true;
    #endif  
  
    settings.vibe_on_disconnect = true;
    settings.date_format = false; 
    settings.flick_display_duration = 10;  
    settings.battery_mode = false;
    settings.battery_warning_level = BATTERY_DEFAULT_WARNING_LVL;
    settings.switch_bin_state = false;
    settings.weather_update_interval=30;

}

void save_settings()
{
    LOG_FUNC_START("save_settings");
  
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));    
  
    window_update();
}

void load_settings()
{
    LOG_FUNC_START("load_settings");
  
    load_default_settings();
  
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

