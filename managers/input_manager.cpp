#include "input_manager.hpp"

Input InputManager::getInputState()
{
  switch (getch())
  {
  case KEY_UP:
    return Input::MOVE_UP;
  case KEY_DOWN:
    return Input::MOVE_DOWN;
  case KEY_LEFT:
    return Input::MOVE_LEFT;
  case KEY_RIGHT:
    return Input::MOVE_RIGHT;
  case ' ':
    return Input::FIRE;
  case 27:
    return Input::EXIT;
  case '\n':
    return Input::SELECT;
  default:
    return Input::NONE;
  }
}