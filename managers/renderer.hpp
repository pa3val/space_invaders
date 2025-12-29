#pragma once
#include "constants.hpp"
#include "entity.hpp"

#include <ncurses.h>
#include <string>

class Renderer
{
public:
  static void draw_char(int x, int y, char ch, ColorPair color_pair);
  static void draw_text(int x, int y, const std::string& text, ColorPair color_pair);
  static void draw_entity(const Entity& entity, ColorPair color_pair);
  static void clear_screen();
  static void refresh_screen();
  static void wait(int millis);
  static void exit_screen();
};