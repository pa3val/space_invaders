#pragma once
#include "constants.hpp"

#include <ncurses.h>

class InputManager
{
public:
  static Input getInputState();
};