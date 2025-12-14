#pragma once
#include <ncurses.h>

enum class ColorPair
{
  BORDER_COLOR = 1,
  PLAYER_COLOR,
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
  NONE
};

const int HEIGHT                 = 25,
          WIDTH                  = 80;
const unsigned short BORDER_SIZE = 1;