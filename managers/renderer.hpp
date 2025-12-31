#pragma once
#include "constants.hpp"
#include "entity.hpp"
#include "signal_manager.hpp"

#include <ncurses.h>
#include <string>

class Renderer
{
private:
  static WINDOW* playfield;
  static WINDOW* info_bar;
  static bool    is_playfield_cleared;
  static bool    is_info_bar_cleared;

public:
  enum class WindowType
  {
    PLAYFIELD,
    INFO_BAR
  };

  static void    init_playfield();
  static void    init_info_bar();
  static void    reset_cleared_flags();
  static void    draw_char(int x, int y, char ch, ColorPair color_pair, WindowType window_type);
  static void    draw_text(int x, int y, const std::string& text, ColorPair color_pair, WindowType window_type);
  static void    draw_entity(const Entity& entity, ColorPair color_pair, WindowType window_type);
  static void    clear_window(WindowType window_type);
  static void    refresh_window(WindowType window_type);
  static void    update_screen();
  static void    wait(int millis);
  static void    destroy_window(WindowType window_type);
  static void    exit_game();
  static WINDOW* get_window(WindowType window_type);
};