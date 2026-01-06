#pragma once
#include "constants.hpp"
#include "entity.hpp"
#include "signal_manager.hpp"

#include <curses.h>
#include <map>
#include <sol/sol.hpp>
#include <string>
#include <windows.h>

class Renderer
{
private:
  static WINDOW*                               playfield;
  static WINDOW*                               info_bar;
  static bool                                  is_playfield_cleared;
  static bool                                  is_info_bar_cleared;
  static std::map<std::string, unsigned short> color_map_;
  struct RGBColor
  {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
  };

public:
  enum class WindowType
  {
    PLAYFIELD,
    INFO_BAR
  };

  static void           initScreen();
  static void           initPlayfield();
  static void           initInfoBar();
  static void           initColorMap();
  static void           resetFlags();
  static void           drawChar(int x, int y, char ch, const std::string& color_name, WindowType window_type);
  static void           drawText(int x, int y, const std::string& text, const std::string& color_name, WindowType window_type);
  static void           drawEntity(const Entity& entity, const std::string& color_name, WindowType window_type);
  static void           clearWindow(WindowType window_type);
  static void           refreshWindow(WindowType window_type);
  static void           updateScreen();
  static void           wait(int millis);
  static void           destroyWindow(WindowType window_type);
  static void           exitGame();
  static WINDOW*        getWindow(WindowType window_type);
  static unsigned short getColor(std::string color_name) { return color_map_[color_name]; }
  static RGBColor       parseColorHex(std::string color_hex);
};