#include <pebble.h>
#include "window.h"
#include "globals.h"
#include "time.h"
#include "gbitmap_color_palette_manipulator.h"
#include "callbacks.h"


/* Load all resources, fonts and bitmaps */
static void load_resources();

/* Create bitmap layers and set bitmaps to them */
static void create_bitmap_layers(GRect bounds);

/* Add all layers (text/bitmap) to the window. */
static void add_layers_to_window(Layer *window_layer);

/* Create text layers and set their preferences. */
static void create_text_layers();

/* Enable tranparency of background in loaded bitmaps. */
static void bitmap_layers_turn_on_transparency();

/* Set up given options to given layer.*/
static void set_up_text_layer(TextLayer *layer, GColor background, GColor text_color, const char * text,GFont font,GTextAlignment alignment);

/* Switch bitmap in given layer.*/
static void switch_bitmap(BitmapLayer *layer, GBitmap *bitmap, int resource);


void window_load(Window *window)
{
  LOG_FUNC_START("window_load");  
  LOG_MEMORY();  
  
  window_layer = window_get_root_layer(window);
  GRect window_full_bounds = layer_get_bounds(window_layer);  
  
  load_resources();
  create_bitmap_layers(window_full_bounds);
  bitmap_layers_turn_on_transparency();
  create_text_layers();
  add_layers_to_window(window_layer);  
  
  switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_FEW_CLOUDS);
   
  LOG_MEMORY();  
  window_update();
  
}

void window_unload(Window *window)
{
  LOG_FUNC_START("window_unload");  
  
  //text layers
  text_layer_destroy(textlayer_menubar);
  text_layer_destroy(textlayer_time);
  text_layer_destroy(textlayer_date);
  text_layer_destroy(textlayer_battery);  
  text_layer_destroy(textlayer_weather);
  text_layer_destroy(textlayer_month);
  text_layer_destroy(textlayer_year);
  
  //bitmap layers
  bitmap_layer_destroy(bitmaplayer_desktop_icons);
  bitmap_layer_destroy(bitmaplayer_desktop_text);
  bitmap_layer_destroy(bitmaplayer_menubar);
  bitmap_layer_destroy(bitmaplayer_datetime_window);
  bitmap_layer_destroy(bitmaplayer_bt);
  bitmap_layer_destroy(bitmaplayer_qt);
  bitmap_layer_destroy(bitmaplayer_battery);
  bitmap_layer_destroy(bitmaplayer_weather);
  
  //bitmaps
  gbitmap_destroy(bitmap_desktop_text);
  gbitmap_destroy(bitmap_desktop_icons);
  gbitmap_destroy(bitmap_menubar);
  gbitmap_destroy(bitmap_datatime_window);
  gbitmap_destroy(bitmap_bt[0]);
  gbitmap_destroy(bitmap_bt[1]);
  
  #ifdef PBL_PLATFORM_APLITE
  gbitmap_destroy(bitmap_qt);  
  #else
  gbitmap_destroy(bitmap_qt[0]);
  gbitmap_destroy(bitmap_qt[1]);
  #endif
  
  gbitmap_destroy(bitmap_battery_icon);
  gbitmap_destroy(bitmap_weather_icon);
  
  //fonts
  fonts_unload_custom_font(font_menubar);
  fonts_unload_custom_font(font_time);
  fonts_unload_custom_font(font_date);
  fonts_unload_custom_font(font_icon_text);  
  fonts_unload_custom_font(font_year_month); 
}

void window_update()
{
  LOG_FUNC_START("window_update");  
   
  bluetooth_callback(connection_service_peek_pebble_app_connection());       
 
  #ifdef PBL_COLOR  
  window_set_background_color(main_window, settings.color_background);     
  text_layer_set_text_color(textlayer_battery,settings.color_text);   
  gbitmap_fill_all_except(GColorClear,settings.color_text,false,bitmap_desktop_text,bitmaplayer_desktop_text);  
  #else //diorite/aplite
  window_set_background_color(main_window, (settings.color_background) ? GColorWhite : GColorBlack);    
  text_layer_set_text_color(textlayer_battery, (settings.color_background) ? GColorBlack : GColorWhite);
  gbitmap_fill_all_except(GColorClear,(settings.color_background) ? GColorBlack : GColorWhite,false,bitmap_desktop_text,bitmaplayer_desktop_text);  
  #endif
    
  display_datetime_window(flick_show_dt_window);
        
  update_time();
  update_date();  
  
  battery_callback(battery_state_service_peek());
  
  LOG_MEMORY();    
}

static void load_resources()
{
  LOG_FUNC_START("load_resources");  
  
  //FONTS
  font_menubar = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_15));
  font_date = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_20));  
  font_time = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_23));
  font_icon_text = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_11));
  font_year_month = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEXT_18));
  
  //BITMAPS
  bitmap_desktop_text = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DESKTOP_TEXTS);
  bitmap_desktop_icons = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DESKTOP_ICONS);  
  bitmap_menubar = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENUBAR);
  bitmap_datatime_window = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DATETIME_WINDOW);
  bitmap_bt[0] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ON);
  bitmap_bt[1] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_OFF);
   
  #ifdef PBL_PLATFORM_APLITE
  bitmap_qt = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QT_OFF);
  #else
  bitmap_qt[0] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QT_ON);
  bitmap_qt[1] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QT_OFF);  
  #endif
    
}

static void create_bitmap_layers(GRect bounds)
{
  LOG_FUNC_START("create_bitmap_layers");
  
  //create bitmap layers
  bitmaplayer_desktop_icons = bitmap_layer_create(bounds);  
  bitmaplayer_desktop_text = bitmap_layer_create(bounds);  
  bitmaplayer_menubar = bitmap_layer_create(GRect(MENUBAR_X,MENUBAR_Y,MENUBAR_W,MENUBAR_H));
  bitmaplayer_datetime_window = bitmap_layer_create(GRect(DT_WINDOW_X,DT_WINDOW_Y,DT_WINDOW_W,DT_WINDOW_H));
  bitmaplayer_bt = bitmap_layer_create(GRect(BT_ICON_X,MB_ICON_Y,MB_ICON_W,MB_ICON_H));
  bitmaplayer_qt = bitmap_layer_create(GRect(QT_ICON_X,MB_ICON_Y,MB_ICON_W,MB_ICON_H));
  bitmaplayer_battery = bitmap_layer_create(GRect(BATTERY_ICON_X,BATTERY_ICON_Y,BATTERY_ICON_W,BATTERY_ICON_H));
  bitmaplayer_weather = bitmap_layer_create(GRect(WEATHER_ICON_X,WEATHER_ICON_Y,WEATHER_ICON_W,WEATHER_ICON_H));
  
  //set corresponding bitmaps to them
  bitmap_layer_set_bitmap(bitmaplayer_desktop_icons,bitmap_desktop_icons);   
  bitmap_layer_set_bitmap(bitmaplayer_desktop_text,bitmap_desktop_text);       
  bitmap_layer_set_bitmap(bitmaplayer_menubar,bitmap_menubar);  
  bitmap_layer_set_bitmap(bitmaplayer_datetime_window,bitmap_datatime_window);  
  bitmap_layer_set_bitmap(bitmaplayer_bt,bitmap_bt[0]); 
  
  #ifdef PBL_PLATFORM_APLITE
  bitmap_layer_set_bitmap(bitmaplayer_qt,bitmap_qt); 
  #else
  bitmap_layer_set_bitmap(bitmaplayer_qt,bitmap_qt[0]); 
  #endif
  
}

static void bitmap_layers_turn_on_transparency()
{
  LOG_FUNC_START("bitmap_layers_turn_on_transparency");
  
  bitmap_layer_set_compositing_mode(bitmaplayer_desktop_icons, GCompOpSet); 
  bitmap_layer_set_compositing_mode(bitmaplayer_desktop_text, GCompOpSet); 
  bitmap_layer_set_compositing_mode(bitmaplayer_menubar, GCompOpSet);   
  bitmap_layer_set_compositing_mode(bitmaplayer_datetime_window, GCompOpSet); 
  bitmap_layer_set_compositing_mode(bitmaplayer_bt, GCompOpSet);   
  bitmap_layer_set_compositing_mode(bitmaplayer_qt, GCompOpSet);   
  bitmap_layer_set_compositing_mode(bitmaplayer_battery, GCompOpSet);   
  bitmap_layer_set_compositing_mode(bitmaplayer_weather, GCompOpSet);   
}

static void add_layers_to_window(Layer *window_layer)
{
  LOG_FUNC_START("add_layers_to_window");
  
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_desktop_icons));
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_desktop_text));
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_menubar));
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_bt));
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_qt));
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_battery));  
  layer_add_child(window_layer,text_layer_get_layer(textlayer_battery));
  layer_add_child(window_layer,text_layer_get_layer(textlayer_menubar));  
  
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_datetime_window));        
  layer_add_child(window_layer,text_layer_get_layer(textlayer_time));
  layer_add_child(window_layer,text_layer_get_layer(textlayer_date));    
  layer_add_child(window_layer,text_layer_get_layer(textlayer_month));
  layer_add_child(window_layer,text_layer_get_layer(textlayer_year));
  layer_add_child(window_layer,text_layer_get_layer(textlayer_weather));    
  layer_add_child(window_layer,bitmap_layer_get_layer(bitmaplayer_weather));
  
}

static void create_text_layers()
{
  LOG_FUNC_START("create_text_layers");
  
  //create layers
  textlayer_menubar = text_layer_create(
    GRect(TIME_MENUBAR_X, TIME_MENUBAR_Y, TIME_MENUBAR_W, TIME_MENUBAR_H));  
  textlayer_time = text_layer_create(
    GRect(TIME_DATETIME_X,TIME_DATETIME_Y, TIME_DATETIME_W, TIME_DATETIME_H));
  textlayer_date = text_layer_create(
    GRect(DATE_DATETIME_X,DATE_DATETIME_Y, DATE_DATETIME_W, DATE_DATETIME_H));
  
  textlayer_month = text_layer_create(
    GRect(MONTH_DATETIME_X,MONTH_DATETIME_Y, MONTH_DATETIME_W, MONTH_DATETIME_H));
  textlayer_year = text_layer_create(
    GRect(YEAR_DATETIME_X,YEAR_DATETIME_Y, YEAR_DATETIME_W, YEAR_DATETIME_H)); 
  
  textlayer_battery = text_layer_create(
    GRect(BATTERY_ICON_TEXT_X, BATTERY_ICON_TEXT_Y,BATTERY_ICON_TEXT_W, BATTERY_ICON_TEXT_H));
  textlayer_weather = text_layer_create(
      GRect(WEATHER_TEXT_X,WEATHER_TEXT_Y,WEATHER_TEXT_W,WEATHER_TEXT_H));
  
  //set up layers with colors, text, fonts etc.
  set_up_text_layer(textlayer_menubar, GColorClear, GColorBlack, "44:44", font_menubar,GTextAlignmentCenter);
  set_up_text_layer(textlayer_time, GColorClear, GColorBlack, "44:44", font_time,GTextAlignmentCenter);
  set_up_text_layer(textlayer_date, GColorClear, GColorWhite, "88", font_date,GTextAlignmentCenter);
  set_up_text_layer(textlayer_month, GColorClear, GColorBlack, "May", font_year_month,GTextAlignmentRight);
  set_up_text_layer(textlayer_year, GColorClear, GColorBlack, "2017", font_year_month,GTextAlignmentLeft);
  set_up_text_layer(textlayer_battery, GColorClear, GColorBlack, "Recycle Bin", font_icon_text,GTextAlignmentCenter);
  set_up_text_layer(textlayer_weather, GColorClear, GColorBlack, "Loading...", font_icon_text,GTextAlignmentLeft);
}

static void set_up_text_layer(TextLayer *layer, GColor background, GColor text_color, const char * text,GFont font,GTextAlignment alignment)
{  
  
  text_layer_set_background_color(layer, background);
  text_layer_set_text_color(layer, text_color);
  text_layer_set_text(layer, text);
  text_layer_set_font(layer, font);
  text_layer_set_text_alignment(layer,alignment); 
}

void display_datetime_window(bool show)
{ 
    LOG_FUNC_START("display_datetime_window");
  
    layer_set_hidden(text_layer_get_layer(textlayer_time),!show);
    layer_set_hidden(text_layer_get_layer(textlayer_date),!show);
    layer_set_hidden(text_layer_get_layer(textlayer_month),!show);
    layer_set_hidden(text_layer_get_layer(textlayer_year),!show);
    layer_set_hidden(text_layer_get_layer(textlayer_weather),!show);
    layer_set_hidden(bitmap_layer_get_layer(bitmaplayer_weather),!show);
    layer_set_hidden(bitmap_layer_get_layer(bitmaplayer_datetime_window),!show);
    
}

void show_battery_menubar()
{
   LOG_FUNC_START("show_battery_menubar");
  
   static char buffer[5];
   snprintf(buffer, sizeof(buffer), "%d%%", battery_level);  
   text_layer_set_text(textlayer_menubar, buffer);    
   
}

void move_layer_vertically(GRect bounds,char offset, Layer *layer)
{  
  // Get the current position of layer
  GRect frame = layer_get_frame(layer);
  // Shift the Y coordinate
  frame.origin.y =  bounds.size.h - offset;
  // Apply the new location
  layer_set_frame(layer, frame);  
}

void update_battery_icon()
{ 
    if(settings.battery_mode) //baterry icon
    {
        //change battery image depending on battery lvl  
        if(battery_level<=100 && battery_level>50)      
            switch_bitmap(bitmaplayer_battery,bitmap_battery_icon,RESOURCE_ID_IMAGE_BATTERY_ICON_100);
        else if (battery_level<=50 && battery_level>25)    
            switch_bitmap(bitmaplayer_battery,bitmap_battery_icon,RESOURCE_ID_IMAGE_BATTERY_ICON_50);
        else if (battery_level<=25 && battery_level>10)
            switch_bitmap(bitmaplayer_battery,bitmap_battery_icon,RESOURCE_ID_IMAGE_BATTERY_ICON_25);
        else
            switch_bitmap(bitmaplayer_battery,bitmap_battery_icon,RESOURCE_ID_IMAGE_BATTERY_ICON_10);
   }
   else
   {
       //change recycle bin image depending on battery lvl  
       if(battery_level<=100 && battery_level>settings.battery_warning_level)
          switch_bitmap(bitmaplayer_battery,bitmap_battery_icon,settings.switch_bin_state ? RESOURCE_ID_IMAGE_BIN_LOW : RESOURCE_ID_IMAGE_BIN_HIGH);
       else     
          switch_bitmap(bitmaplayer_battery,bitmap_battery_icon,settings.switch_bin_state ? RESOURCE_ID_IMAGE_BIN_HIGH : RESOURCE_ID_IMAGE_BIN_LOW);     
   }
    
}

void update_weather_text_icon(const char * temp, uint8_t icon_num)
{
    LOG_FUNC_START("update_weather_text_icon");
    APP_LOG(APP_LOG_LEVEL_DEBUG, "icon number %d",icon_num);
  
    static char temperature_buffer[8];
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", temp);
    text_layer_set_text(textlayer_weather, temperature_buffer);
  
    switch(icon_num){
        case 1:
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_CLEAR_SKY);
            break;
        case 2:
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_FEW_CLOUDS);
            break;
        case 3:
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_BROKEN_CLOUDS);
            break;
        case 4:
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_RAIN);
            break;
        case 5:
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_THUNDERSTORM);
            break;
        case 6:
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_SNOW);
            break;
        case 7:   
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_MIST);
            break;      
        default:
            switch_bitmap(bitmaplayer_weather,bitmap_weather_icon,RESOURCE_ID_IMAGE_NOT_AVAILABLE);
            break;
  }
  
  
}

static void switch_bitmap(BitmapLayer *layer,GBitmap *bitmap, int resource)
{
    LOG_FUNC_START("switch_bitmap");
    gbitmap_destroy(bitmap);
    bitmap = gbitmap_create_with_resource(resource);
    bitmap_layer_set_bitmap(layer,bitmap);     
}

