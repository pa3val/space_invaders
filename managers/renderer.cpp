#include "renderer.hpp"

void Renderer::draw_char(int x, int y, char ch, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  attron(COLOR_PAIR(color));
  mvaddch(y, x, ch);
  attroff(COLOR_PAIR(color));
}

void Renderer::draw_text(int x, int y, const char* text, ColorPair color_pair)
{
  int color = static_cast<int>(color_pair);
  attron(COLOR_PAIR(color));
  mvprintw(y, x, "%s", text);
  attroff(COLOR_PAIR(color));
}

void Renderer::refresh_screen()
{
  refresh();
}

void Renderer::clear_screen()
{
  clear();
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