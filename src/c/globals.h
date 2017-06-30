#pragma once
#include <pebble.h>

//COORDINATES

//MENUBAR
#define MENUBAR_X 0
#define MENUBAR_Y 140
#define MENUBAR_W 144
#define MENUBAR_H 28

//ICONS - MY COMPUTER/DOCUMENTS
#define ICONS_X 0
#define ICONS_Y 0
#define ICONS_W 144
#define ICONS_H 51

//ICONS TEXTS
#define ICONS_TEXTS_X 0
#define ICONS_TEXTS_Y 0
#define ICONS_TEXTS_W 144
#define ICONS_TEXTS_H 51  

//DATETIME WINDOW
#define DT_WINDOW_X 19
#define DT_WINDOW_Y 9
#define DT_WINDOW_W 120
#define DT_WINDOW_H 117

//MENUBAR ICONS
#define MB_ICON_W 16
#define MB_ICON_H 16
#define MB_ICON_Y 147
#define BT_ICON_X 65
#define QT_ICON_X 83

//BATTERY ICON AND TEXT
#define BATTERY_ICON_X 16
#define BATTERY_ICON_Y 70
#define BATTERY_ICON_W 32
#define BATTERY_ICON_H 32

#define BATTERY_ICON_TEXT_X 0
#define BATTERY_ICON_TEXT_Y 106
#define BATTERY_ICON_TEXT_W 65
#define BATTERY_ICON_TEXT_H 15

//WEATHER ICON AND TEXT
#define WEATHER_ICON_X 90
#define WEATHER_ICON_Y 70
#define WEATHER_ICON_W 32
#define WEATHER_ICON_H 32

#define WEATHER_ICON_TEXT_X 74
#define WEATHER_ICON_TEXT_Y 106
#define WEATHER_ICON_TEXT_W 69
#define WEATHER_ICON_TEXT_H 15

//TEXTS
#define TIME_MENUBAR_X 101
#define TIME_MENUBAR_Y 145
#define TIME_MENUBAR_W 38
#define TIME_MENUBAR_H 20

#define TIME_DATETIME_X DT_WINDOW_X + 10
#define TIME_DATETIME_Y DT_WINDOW_Y + 38
#define TIME_DATETIME_W 100
#define TIME_DATETIME_H 28

#define DATE_DATETIME_X DT_WINDOW_X + 10
#define DATE_DATETIME_Y DT_WINDOW_Y + 89
#define DATE_DATETIME_W 100
#define DATE_DATETIME_H 16

//OTHERS
#define BATTERY_STATES_NUM 4
#define BATTERY_DEFAULT_WARNING_LVL 40

// Persistent storage key for connection status
#define CONNECTED_KEY 2623

// Persistent storage key for settings
#define SETTINGS_KEY 72631

 
Window *main_window;
GRect window_full_bounds;
Layer *window_layer;

TextLayer *textlayer_menubar, *textlayer_time, *textlayer_date, *textlayer_battery, *textlayer_weather;

BitmapLayer *bitmaplayer_desktop_icons,*bitmaplayer_desktop_text, *bitmaplayer_menubar,*bitmaplayer_datetime_window,*bitmaplayer_bt, *bitmaplayer_qt, *bitmaplayer_battery;                          
  
GBitmap *bitmap_desktop_text, *bitmap_desktop_icons, *bitmap_menubar, *bitmap_datatime_window,*bitmap_bt[2],
        *bitmap_battery_bin[2], *bitmap_battery_icon[4];                        

#ifdef PBL_PLATFORM_APLITE
GBitmap *bitmap_qt;
#else
GBitmap *bitmap_qt[2];  
#endif


GFont font_menubar, font_date, font_time, font_icon_text;

GColor color_desktop_text;
uint8_t battery_level;
AppTimer *timer;
bool flick_show_dt_window;
bool is_connected; //to prevent vibration every time window is loaded

//SETTINGS STRUCT
typedef struct ClaySettings {
  #ifdef PBL_COLOR
  GColor color_background;
  GColor color_text;
  #endif
  
  #ifdef PBL_BW
  bool color_background; //false = black
  #endif
  
  bool vibe_on_disconnect;  
  bool date_format;
  char flick_display_duration;  
  bool battery_mode; //false = Recycle Bin
  char battery_warning_level;
  bool switch_bin_state;
  bool weather_enabled;
  bool weather_unit; //false - fahrenheit
  bool weather_gps_on; 
  uint8_t weather_interval;
} ClaySettings;

ClaySettings settings;



