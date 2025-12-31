#include "renderer.hpp"

WINDOW* Renderer::playfield            = nullptr;
WINDOW* Renderer::info_bar             = nullptr;
bool    Renderer::is_playfield_cleared = false;
bool    Renderer::is_info_bar_cleared  = false;

void Renderer::init_playfield()
{
  playfield = newwin(PLAYFIELD_HEIGHT, PLAYFIELD_WIDTH, INFO_BAR_HEIGHT, 0);
}

void Renderer::init_info_bar()
{
  info_bar = newwin(INFO_BAR_HEIGHT, INFO_BAR_WIDTH, 0, 0);
}

void Renderer::reset_cleared_flags()
{
  is_playfield_cleared = false;
  is_info_bar_cleared  = false;
}

WINDOW* Renderer::get_window(WindowType window_type)
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
void Renderer::draw_char(int x, int y, char ch, ColorPair color_pair, WindowType window_type)
{
  WINDOW* window = get_window(window_type);
  if (!window)
    return;
  int color = static_cast<int>(color_pair);
  wattron(window, COLOR_PAIR(color));
  mvwaddch(window, y, x, ch);
  wattroff(window, COLOR_PAIR(color));
}

void Renderer::draw_text(int x, int y, const std::string& text, ColorPair color_pair, WindowType window_type)
{
  WINDOW* window = get_window(window_type);
  if (!window)
    return;
  int color = static_cast<int>(color_pair);
  wattron(window, COLOR_PAIR(color));
  mvwprintw(window, y, x, "%s", text.c_str());
  wattroff(window, COLOR_PAIR(color));
}

void Renderer::draw_entity(const Entity& entity, ColorPair color_pair, WindowType window_type)
{
  WINDOW* window = get_window(window_type);
  if (!window)
    return;
  int color = static_cast<int>(color_pair);
  wattron(window, COLOR_PAIR(color));

  for (int i = 0; i < entity.getHeight(); ++i)
  {
    for (int j = 0; j < entity.getWidth(); ++j)
    {
      mvwaddch(
          window,
          i + entity.getPosY(),
          j + entity.getPosX(),
          entity.getAppearance()[i][j]);
    }
  }
  wattroff(window, COLOR_PAIR(color));
}

void Renderer::refresh_window(WindowType window_type)
{
  WINDOW* window = (window_type == WindowType::PLAYFIELD) ? playfield : info_bar;
  if (!window)
    return;
  wattron(window, COLOR_PAIR(ColorPair::BORDER_COLOR));
  box(window, 0, 0);
  wattroff(window, COLOR_PAIR(ColorPair::BORDER_COLOR));
  wnoutrefresh(window);
}

void Renderer::update_screen()
{
  doupdate();
}

void Renderer::clear_window(WindowType window_type)
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

void Renderer::destroy_window(WindowType window_type)
{
  WINDOW* window = (window_type == WindowType::PLAYFIELD) ? playfield : info_bar;
  if (!window)
    return;
  werase(window);
  refresh_window(window_type);
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

void Renderer::exit_game()
{
  destroy_window(WindowType::PLAYFIELD);
  destroy_window(WindowType::INFO_BAR);
  curs_set(1);
  endwin();
}