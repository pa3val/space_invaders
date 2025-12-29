#include "renderer.hpp"

void Renderer::draw_char(int x, int y, char ch, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  attron(COLOR_PAIR(color));
  mvaddch(y, x, ch);
  attroff(COLOR_PAIR(color));
}

void Renderer::draw_text(int x, int y, const std::string& text, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  attron(COLOR_PAIR(color));
  mvprintw(y, x, "%s", text.c_str());
  attroff(COLOR_PAIR(color));
}

void Renderer::draw_entity(const Entity& entity, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  attron(COLOR_PAIR(color));

  for (int i = 0; i < entity.getHeight(); ++i)
  {
    for (int j = 0; j < entity.getWidth(); ++j)
    {
      mvaddch(
          i + entity.getPosY(),
          j + entity.getPosX(),
          entity.getAppearance()[i][j]);
    }
  }
  attroff(COLOR_PAIR(color));
}

void Renderer::refresh_screen()
{
  attron(COLOR_PAIR(ColorPair::BORDER_COLOR));
  box(stdscr, 0, 0);
  attroff(COLOR_PAIR(ColorPair::BORDER_COLOR));

  refresh();
}

void Renderer::clear_screen()
{
  erase();
}

void Renderer::wait(int millis)
{
  napms(millis);
}

void Renderer::exit_screen()
{
  curs_set(1);
  endwin();
}