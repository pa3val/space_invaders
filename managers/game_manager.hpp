#pragma once

#include "game_state.hpp"
#include "input_manager.hpp"
#include "level_state.hpp"
#include "menu_state.hpp"
#include "renderer.hpp"
#include "signal_manager.hpp"

#include <memory>
#include <ncurses.h>

class GameManager
{
private:
  std::unique_ptr<GameState> state_;

public:
  GameManager();
  void initScreen();
  void initColors();
  void runGame();
  void handleSignal();
};