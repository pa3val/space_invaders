#pragma once
#include <ncurses.h>

enum class ColorPair
{
  ENEMY_COLOR = 1,
  PLAYER_COLOR,
  BORDER_COLOR,
  BULLET_COLOR,
  TEXT_COLOR,
  SELECTED_TEXT_COLOR
};

enum class Input
{
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  FIRE,
  PAUSE,
  EXIT,
  SELECT,
  NONE
};

enum class Signals
{
  EXIT,
  CHANGE_TO_LEVEL,
  CHANGE_TO_MENU,
  GAME_OVER,
  NONE
};

constexpr int HEIGHT                 = 30,
              WIDTH                  = 80;
constexpr unsigned short BORDER_SIZE = 1;