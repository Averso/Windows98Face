#include <pebble.h>
#include "weather.h"
#include "globals.h"

void update_temperature() {
    static char s_buffer[25];
    APP_LOG(APP_LOG_LEVEL_ERROR, "Temp is: %d", temperature);
    if (settings.temperature_format) {
        snprintf(s_buffer, sizeof(s_buffer), "%d", temperature);
    }
    else {
        snprintf(s_buffer, sizeof(s_buffer), "%d", (int)(32 + ((temperature) * 1.8 )));
    }
    text_layer_set_text(layer_weather_text, s_buffer);
}

void enable_weather(bool enableWeather) {
  layer_set_hidden(text_layer_get_layer(layer_weather_text),!enableWeather);
  layer_set_hidden(bitmap_layer_get_layer(layer_bt),enableWeather);
  layer_set_hidden(bitmap_layer_get_layer(layer_qt),enableWeather);
}