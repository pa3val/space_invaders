#pragma once

#include "audio_manager.hpp"
#include "constants.hpp"
#include "game_over_state.hpp"
#include "game_state.hpp"
#include "input_manager.hpp"
#include "level_state.hpp"
#include "menu_state.hpp"
#include "renderer.hpp"
#include "signal_manager.hpp"

#include <curses.h>
#include <memory>

class GameManager
{
private:
  std::unique_ptr<GameState> state_ = std::make_unique<LevelState>();

public:
  GameManager();
  void runGame();
  void handleSignal();
};