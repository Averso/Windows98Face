#include <pebble.h>
#include "window.h"
#include "globals.h"
#include "callbacks.h"
#include "time.h"
#include "gbitmap_color_palette_manipulator.h"

void window_load(Window *window)  
{
  //get window layer and bounds
  Layer *window_layer = window_get_root_layer(window);  
  GRect bounds = layer_get_bounds(window_layer);
    
      
  load_resources(); 
  create_bitmap_layers(bounds);
  create_text_layers();
  
  bitmap_layers_turn_on_transparency();
  add_layers_to_window(window_layer);
 
  window_update();  
  
}

void window_unload(Window *window)
{
//    APP_LOG(APP_LOG_LEVEL_DEBUG, "window unload");
  text_layer_destroy(layer_menubar_text);
  text_layer_destroy(layer_time);
  text_layer_destroy(layer_date);
  text_layer_destroy(layer_battery_text);
  
  //destroy bitmaps
  gbitmap_destroy(bitmap_desktop_text); 
  gbitmap_destroy(bitmap_desktop_icons);
  gbitmap_destroy(bitmap_menubar);
  gbitmap_destroy(bitmap_window);
  gbitmap_destroy(bitmap_bt_on);
  gbitmap_destroy(bitmap_bt_off);
  gbitmap_destroy(bitmap_qt_on);
  gbitmap_destroy(bitmap_qt_off);
  gbitmap_destroy(bitmap_battery_high);
  gbitmap_destroy(bitmap_battery_low);
  
  for(int i=0; i<BATTERY_LVLS;i++)  
    gbitmap_destroy(bitmap_battery_icon[i]);     
  
  
            
  bitmap_layer_destroy(layer_desktop_text);
  bitmap_layer_destroy(layer_desktop_icons);
  bitmap_layer_destroy(layer_menubar);
  bitmap_layer_destroy(layer_window);
  bitmap_layer_destroy(layer_bt);
  bitmap_layer_destroy(layer_qt);
  bitmap_layer_destroy(layer_battery);
  
  
  fonts_unload_custom_font(font_menubar);
  fonts_unload_custom_font(font_time);
  fonts_unload_custom_font(font_date);
  fonts_unload_custom_font(font_icon_text);
 
}

void window_update()
{
  //check bt status
  bluetooth_callback(connection_service_peek_pebble_app_connection());     
  
  //background color   
  #ifdef PBL_COLOR 
 
  window_set_background_color(main_window, settings.bg_color); 
  
  //change text color
  text_layer_set_text_color(layer_battery_text,settings.text_color);  
  gbitmap_fill_all_except(GColorClear,settings.text_color,false,bitmap_desktop_text,layer_desktop_text);
  
  #else //diorite/aplite
  if(settings.bg_color) //black desktop
  {
    window_set_background_color(main_window, GColorWhite);
    //change text color
    text_layer_set_text_color(layer_battery_text,GColorBlack);  
    gbitmap_fill_all_except(GColorClear,GColorBlack,false,bitmap_desktop_text,layer_desktop_text);     
  }
  else //white desktop
  {
    window_set_background_color(main_window, GColorBlack);
    //change text color
    text_layer_set_text_color(layer_battery_text,GColorWhite);    
    gbitmap_fill_all_except(GColorClear,GColorWhite,false,bitmap_desktop_text,layer_desktop_text);
  }    
  #endif
  
  
  //show/hide and change position of data/time window
  
  if(settings.show_datatime_window)
  {
    layer_set_frame(bitmap_layer_get_layer(layer_window),
                    GRect(WINDOW_X,WINDOW_Y,WINDOW_W,WINDOW_H));
    
    layer_set_frame(text_layer_get_layer(layer_time),
                    GRect(WINDOW_X + TIME_BIG_X_OFFSET,WINDOW_Y + TIME_BIG_Y_OFFSET,TIME_BIG_W,TIME_BIG_H));
    
    layer_set_frame(text_layer_get_layer(layer_date),
                    GRect(WINDOW_X + DATE_X_OFFSET,WINDOW_Y + DATE_Y_OFFSET,DATE_W,DATE_H));
  }

  show_datatime_window((settings.show_datatime_window && !settings.flick_enabled));
    
  
  update_time();
  update_date();
  
  //check battery - to update menubar text if needed  
  battery_callback(battery_state_service_peek());
  
  // subscribe to tap events
  if(settings.flick_enabled)
    accel_tap_service_subscribe(accel_tap_handler);
  
}

void load_resources()
{
  
  //FONTS
  font_menubar = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_15));
  font_date = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_13));  
  font_time = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_23));
  font_icon_text = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_11));
  
  //BITMAPS
  bitmap_desktop_text = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DESKTOP_TEXT);
  bitmap_desktop_icons = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DESKTOP_ICONS);  
  bitmap_menubar = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENUBAR);
  bitmap_window = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_WINDOW);
  bitmap_bt_on = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ON);
  bitmap_bt_off = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_OFF);
  bitmap_qt_on = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QT_ON);
  bitmap_qt_off = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QT_OFF);
  bitmap_battery_high = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_HIGH);
  bitmap_battery_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_LOW);
  bitmap_battery_icon[0] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_100);
  bitmap_battery_icon[1] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_50);
  bitmap_battery_icon[2] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_25);
  bitmap_battery_icon[3] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_10);

  

  
}

void create_bitmap_layers(GRect bounds)
{   
    
  layer_desktop_icons = bitmap_layer_create(bounds);  
  layer_desktop_text = bitmap_layer_create(bounds);  
  layer_menubar = bitmap_layer_create(GRect(MENUBAR_X,MENUBAR_Y,MENUBAR_W,MENUBAR_H));
  layer_window = bitmap_layer_create(GRect(WINDOW_X,WINDOW_Y,WINDOW_W,WINDOW_H));
  layer_bt = bitmap_layer_create(GRect(BT_X,ICON_Y,ICON_W,ICON_H));
  layer_qt = bitmap_layer_create(GRect(QT_X,ICON_Y,ICON_W,ICON_H));
  layer_battery = bitmap_layer_create(GRect(BATTERY_X,BATTERY_Y,BATTERY_W,BATTERY_H));
  
  bitmap_layer_set_bitmap(layer_desktop_text,bitmap_desktop_text);      
  bitmap_layer_set_bitmap(layer_desktop_icons,bitmap_desktop_icons);   
  bitmap_layer_set_bitmap(layer_menubar,bitmap_menubar);  
  bitmap_layer_set_bitmap(layer_window,bitmap_window);  
  bitmap_layer_set_bitmap(layer_bt,bitmap_bt_off); 
  bitmap_layer_set_bitmap(layer_qt,bitmap_qt_off); 
  bitmap_layer_set_bitmap(layer_battery,bitmap_battery_high);  
    
}

void create_text_layers()
{  
  layer_menubar_text = text_layer_create(
    GRect(TIME_SMALL_X, TIME_SMALL_Y, TIME_SMALL_W, TIME_SMALL_H));  
  layer_time = text_layer_create(
    GRect(TIME_BIG_X, TIME_BIG_Y, TIME_BIG_W, TIME_BIG_H));   
  layer_date = text_layer_create(
    GRect(DATE_X, DATE_Y,DATE_W, DATE_H));
  layer_battery_text = text_layer_create(
    GRect(BATTERY_TEXT_X, BATTERY_TEXT_Y,BATTERY_TEXT_W, BATTERY_TEXT_H));
  
  set_up_text_layer(layer_menubar_text, GColorClear, GColorBlack, "44:44", font_menubar,GTextAlignmentCenter);
  set_up_text_layer(layer_time, GColorClear, GColorBlack, "44:44", font_time,GTextAlignmentCenter);
  set_up_text_layer(layer_date, GColorClear, GColorBlack, "44-44-2044", font_date,GTextAlignmentCenter);
  set_up_text_layer(layer_battery_text, GColorClear, GColorWhite, "Recycle Bin", font_icon_text,GTextAlignmentCenter);
}

void set_up_text_layer(TextLayer *layer, GColor background, GColor text_color, const char * text,GFont font,GTextAlignment alignment)
{
  text_layer_set_background_color(layer, background);
  text_layer_set_text_color(layer, text_color);
  text_layer_set_text(layer, text);
  text_layer_set_font(layer, font);
  text_layer_set_text_alignment(layer,alignment); 
}

void bitmap_layers_turn_on_transparency()
{
  bitmap_layer_set_compositing_mode(layer_desktop_icons, GCompOpSet); 
  bitmap_layer_set_compositing_mode(layer_desktop_text, GCompOpSet); 
  bitmap_layer_set_compositing_mode(layer_menubar, GCompOpSet);   
  bitmap_layer_set_compositing_mode(layer_window, GCompOpSet); 
  bitmap_layer_set_compositing_mode(layer_bt, GCompOpSet);   
  bitmap_layer_set_compositing_mode(layer_qt, GCompOpSet);   
  bitmap_layer_set_compositing_mode(layer_battery, GCompOpSet);   
  
}

void add_layers_to_window(Layer *window_layer)
{
  //bitmaps
  layer_add_child(window_layer,bitmap_layer_get_layer(layer_desktop_icons));
  layer_add_child(window_layer,bitmap_layer_get_layer(layer_desktop_text));
  layer_add_child(window_layer,bitmap_layer_get_layer(layer_menubar));
  layer_add_child(window_layer,bitmap_layer_get_layer(layer_bt));
  layer_add_child(window_layer,bitmap_layer_get_layer(layer_qt));
  layer_add_child(window_layer,bitmap_layer_get_layer(layer_battery));  
  layer_add_child(window_layer,bitmap_layer_get_layer(layer_window));
  
  //text
  layer_add_child(window_layer,text_layer_get_layer(layer_menubar_text));  
  layer_add_child(window_layer,text_layer_get_layer(layer_time));
  layer_add_child(window_layer,text_layer_get_layer(layer_date));
  layer_add_child(window_layer,text_layer_get_layer(layer_battery_text));
}

void show_datatime_window(bool show_datatime_window)
{
    layer_set_hidden(text_layer_get_layer(layer_time),!show_datatime_window);
    layer_set_hidden(text_layer_get_layer(layer_date),!show_datatime_window);
    layer_set_hidden(bitmap_layer_get_layer(layer_window),!show_datatime_window);
}
