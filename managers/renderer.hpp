#pragma once
#include "constants.hpp"

#include <ncurses.h>

class Renderer
{
public:
  static void draw_char(int x, int y, char ch, ColorPair color_pair);
  static void draw_text(int x, int y, const char* text, ColorPair color_pair);
  static void clear_screen();
  static void refresh_screen();
  static void wait(int millis);
  static void exit_screen();
};