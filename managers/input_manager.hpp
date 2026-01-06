#pragma once
#include "constants.hpp"

#include <curses.h>

class InputManager
{
public:
  static Input getInputState();
};