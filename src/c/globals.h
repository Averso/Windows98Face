#pragma once
#include <pebble.h>


#define MENUBAR_X 0
#define MENUBAR_Y 140
#define MENUBAR_W 144
#define MENUBAR_H 28

#define DESKTOP_X 0
#define DESKTOP_Y 0
#define DESKTOP_W 144
#define DESKTOP_H 51

#define DSKTOP_TEXT_X 0
#define DSKTOP_TEXT_Y 0
#define DSKTOP_TEXT_W 144
#define DSKTOP_TEXT_H 51  

#define WINDOW_X 19
#define WINDOW_Y 9
#define WINDOW_W 120
#define WINDOW_H 124

#define ICON_W 16
#define ICON_H 16
#define ICON_Y 147

#define BT_X 65

#define QT_X 83

#define BATTERY_X 16
#define BATTERY_Y 70
#define BATTERY_W 32
#define BATTERY_H 32

#define BATTERY_TEXT_X 0
#define BATTERY_TEXT_Y 106
#define BATTERY_TEXT_W 65
#define BATTERY_TEXT_H 15


#define TIME_SMALL_X 101
#define TIME_SMALL_Y 145
#define TIME_SMALL_W 38
#define TIME_SMALL_H 20

#define TIME_BIG_X 33
#define TIME_BIG_Y 60
#define TIME_BIG_W 100
#define TIME_BIG_H 28

#define DATE_X 33
#define DATE_Y 102
#define DATE_W 100
#define DATE_H 16

#define TIME_BIG_X_OFFSET 10
#define TIME_BIG_Y_OFFSET 41

#define DATE_X_OFFSET 10
#define DATE_Y_OFFSET 96

#define BATTERY_LVLS 4

#define BETTERY_DEFAULT_LVL 40

// Persistent storage key for connection status
#define CONNECTED_KEY 2623

// Persistent storage key for settings
#define SETTINGS_KEY 72631

Window *main_window;                                  

TextLayer *layer_menubar_text, *layer_time, *layer_date, *layer_battery_text, *layer_weather_text;

BitmapLayer *layer_desktop_icons,*layer_desktop_text, *layer_menubar,*layer_window,*layer_bt, *layer_qt, *layer_battery;                          

GBitmap *bitmap_desktop_text, *bitmap_desktop_icons, *bitmap_menubar,*bitmap_window,*bitmap_bt_on,*bitmap_bt_off,
        *bitmap_qt_on,*bitmap_qt_off,*bitmap_battery_high, *bitmap_battery_low, *bitmap_battery_icon[4];                        

GFont font_menubar, font_date, font_time, font_icon_text;

GColor color_desktop_text;
int battery_level;
AppTimer *timer;

bool flick_show_window;


typedef struct ClaySettings {
  #ifdef PBL_COLOR
  GColor bg_color;
  GColor text_color;
  #endif
  #ifdef PBL_BW
  bool bg_color; //false = black
  #endif
  bool vibe_on_disconnect;
  int battery_warning_level;
  bool show_datatime_window;
  bool switch_bin_state;
  bool date_format;
  bool flick_enabled;
  char flick_show_duration;
  bool battery_mode; //false = Recycle Bin
  bool battery_text; //false = 'Recycle Bin' text
} ClaySettings;

// An instance of the struct
ClaySettings settings;