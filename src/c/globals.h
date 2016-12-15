#pragma once
#include <pebble.h>


#define MENUBAR_X 0
#define MENUBAR_Y 140
#define MENUBAR_W 144
#define MENUBAR_H 28

#define DESKTOP_X 0
#define DESKTOP_Y 0
#define DESKTOP_W 144
#define DESKTOP_H 168

#define WINDOW_X 23
#define WINDOW_Y 23
#define WINDOW_W 116
#define WINDOW_H 108

#define ICON_W 16
#define ICON_H 16
#define ICON_Y 147

#define BT_X 65

#define QT_X 83

#define BATTERY_X 16
#define BATTERY_Y 70
#define BATTERY_W 32
#define BATTERY_H 32

#define TIME_SMALL_X 101
#define TIME_SMALL_Y 145
#define TIME_SMALL_W 38
#define TIME_SMALL_H 20

#define TIME_BIG_X 33
#define TIME_BIG_Y 60
#define TIME_BIG_W 96
#define TIME_BIG_H 15

#define DATE_X 33
#define DATE_Y 102
#define DATE_W 96
#define DATE_H 15

#define TIME_BIG_X_REL 10
#define TIME_BIG_Y_REL 38

#define DATE_X_REL 10
#define DATE_Y_REL 80

#define BETTERY_DEFAULT_LVL 40
#define CONNECTED_KEY 12

#define WINDOW_CENTER_X 14
#define WINDOW_CENTER_Y 23

Window *main_window;                                  

TextLayer *layer_menubar_text, *layer_time, *layer_date;
BitmapLayer *layer_desktop, *layer_menubar,*layer_window,*layer_bt, *layer_qt, *layer_battery;                          
GBitmap *bitmap_desktop, *bitmap_menubar,*bitmap_window,*bitmap_bt_on,*bitmap_bt_off,
        *bitmap_qt_on,*bitmap_qt_off,*bitmap_battery_high, *bitmap_battery_low;                          
GFont font_menubar, font_window;

int battery_level;


//settings struct
typedef struct ClaySettings {
  GColor bg_color;
  bool vibe_on_disconnect;
  int battery_warning_level;
  char window_x;
  char window_y;
  bool show_datatime_window;
  bool center_pos;
} ClaySettings;

// An instance of the struct
ClaySettings settings;