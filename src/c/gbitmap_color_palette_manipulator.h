// https://github.com/rebootsramblings/GBitmap-Colour-Palette-Manipulator
#pragma once
#include <pebble.h>

void gbitmap_fill_all_except(GColor color_to_not_change, GColor fill_color, bool fill_gcolorclear, GBitmap *im, BitmapLayer *bml);


