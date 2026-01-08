#include "renderer.hpp"

WINDOW*                                         Renderer::playfield            = nullptr;
WINDOW*                                         Renderer::info_bar             = nullptr;
bool                                            Renderer::is_playfield_cleared = false;
bool                                            Renderer::is_info_bar_cleared  = false;
std::unordered_map<std::string, unsigned short> Renderer::color_map_           = {};

void Renderer::initScreen()
{
  HWND hwnd = GetConsoleWindow();
  if (hwnd != NULL)
  {
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
    style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
    SetWindowLongPtr(hwnd, GWL_STYLE, style);

    SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
  }

  printf("\033[8;%d;%dt", SCREEN_HEIGHT, SCREEN_WIDTH);
  fflush(stdout);
  initscr();
  resize_term(SCREEN_HEIGHT, SCREEN_WIDTH);
  Renderer::initInfoBar();
  Renderer::initPlayfield();
  start_color();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
  raw();
  noecho();
}
void Renderer::initPlayfield()
{
  playfield = newwin(PLAYFIELD_HEIGHT, PLAYFIELD_WIDTH, INFO_BAR_HEIGHT, 0);
}

void Renderer::initInfoBar()
{
  info_bar = newwin(INFO_BAR_HEIGHT, INFO_BAR_WIDTH, 0, 0);
}

void Renderer::initColorMap()
{
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("global_config.lua");
  sol::table     colors            = lua["colors"];
  unsigned short color_pair_number = 1;
  for (auto& [key, value] : colors)
  {
    RGBColor color = parseColorHex(value.as<std::string>());
    init_color(color_pair_number, color.red, color.green, color.blue);
    if (key.as<std::string>() == "SELECTED_TEXT_COLOR")
      init_pair(color_pair_number, COLOR_BLACK, color_pair_number);
    else
      init_pair(color_pair_number, color_pair_number, COLOR_BLACK);
    color_map_[key.as<std::string>()] = color_pair_number;
    ++color_pair_number;
  }
}

void Renderer::resetFlags()
{
  is_playfield_cleared = false;
  is_info_bar_cleared  = false;
}

WINDOW* Renderer::getWindow(WindowType window_type)
{
  switch (window_type)
  {
  case WindowType::PLAYFIELD:
    if (!is_playfield_cleared)
    {
      werase(playfield);
      is_playfield_cleared = true;
    }
    SignalManager::setDrawFlag(SignalManager::DrawFlags::DRAW_PLAYFIELD);
    return playfield;
  case WindowType::INFO_BAR:
    if (!is_info_bar_cleared)
    {
      werase(info_bar);
      is_info_bar_cleared = true;
    }
    SignalManager::setDrawFlag(SignalManager::DrawFlags::DRAW_INFO_BAR);
    return info_bar;
  }
  return nullptr;
}
void Renderer::drawChar(int x, int y, char ch, WindowType window_type)
{
  WINDOW* window = getWindow(window_type);
  if (!window)
    return;
  int color = getColor("TEXT_COLOR");
  wattron(window, COLOR_PAIR(color));
  mvwaddch(window, y, x, ch);
  wattroff(window, COLOR_PAIR(color));
}

void Renderer::drawText(int x, int y, const std::string& text, bool is_selected, WindowType window_type)
{
  WINDOW* window = getWindow(window_type);
  if (!window)
    return;
  int color = is_selected ? getColor("SELECTED_TEXT_COLOR") : getColor("TEXT_COLOR");
  wattron(window, COLOR_PAIR(color));
  mvwprintw(window, y, x, "%s", text.c_str());
  wattroff(window, COLOR_PAIR(color));
}

void Renderer::drawEntity(const Entity& entity, WindowType window_type)
{
  WINDOW* window = getWindow(window_type);
  if (!window)
    return;
  unsigned short color = entity.getColorPair();
  wattron(window, COLOR_PAIR(color));
  const std::vector<std::vector<char>>* current_frame;
  if (entity.animator_.isAnimationRunning() && !entity.animator_.isAnimationFinished())
  {
    current_frame = &entity.animator_.getCurrentFrame();
  }
  else
  {
    current_frame = &entity.getAppearance();
  }

  for (int i = 0; i < entity.getHeight(); ++i)
  {
    for (int j = 0; j < entity.getWidth(); ++j)
    {
      mvwaddch(
          window,
          i + entity.getPosY(),
          j + entity.getPosX(),
          (*current_frame)[i][j]);
    }
  }
  wattroff(window, COLOR_PAIR(color));
}

void Renderer::refreshWindow(WindowType window_type)
{
  WINDOW* window = (window_type == WindowType::PLAYFIELD) ? playfield : info_bar;
  if (!window)
    return;
  int color = getColor("BORDER_COLOR");
  wattron(window, COLOR_PAIR(color));
  box(window, 0, 0);
  wattroff(window, COLOR_PAIR(color));
  wnoutrefresh(window);
}

void Renderer::updateScreen()
{
  doupdate();
}

void Renderer::clearWindow(WindowType window_type)
{
  WINDOW* window = (window_type == WindowType::PLAYFIELD) ? playfield : info_bar;
  if (!window)
    return;
  werase(window);
}

void Renderer::wait(int millis)
{
  napms(millis);
}

void Renderer::destroyWindow(WindowType window_type)
{
  WINDOW* window = (window_type == WindowType::PLAYFIELD) ? playfield : info_bar;
  if (!window)
    return;
  werase(window);
  refreshWindow(window_type);
  delwin(window);
  switch (window_type)
  {
  case WindowType::PLAYFIELD:
    playfield = nullptr;
    break;
  case WindowType::INFO_BAR:
    info_bar = nullptr;
    break;
  }
}

void Renderer::exitGame()
{
  destroyWindow(WindowType::PLAYFIELD);
  destroyWindow(WindowType::INFO_BAR);
  curs_set(1);
  endwin();
}

Renderer::RGBColor Renderer::parseColorHex(std::string color_hex)
{
  RGBColor color;
  if (color_hex[0] == '#')
    color_hex.erase(0, 1);
  color.red   = std::stoi(color_hex.substr(0, 2), nullptr, 16) * 1000 / 255;
  color.green = std::stoi(color_hex.substr(2, 2), nullptr, 16) * 1000 / 255;
  color.blue  = std::stoi(color_hex.substr(4, 2), nullptr, 16) * 1000 / 255;
  return color;
}