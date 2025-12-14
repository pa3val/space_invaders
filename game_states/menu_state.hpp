#pragma once
#include "constants.hpp"
#include "game_state.hpp"
#include "signal_manager.hpp"
#include "renderer.hpp"

#include <array>
#include <cstdlib>
#include <cstring>

class MenuState : public GameState
{
private:
  std::size_t                selected_item_ = 0;
  std::array<const char*, 2> menu_text_     = {
    "Start",
    "Exit"
  };

public:
  MenuState();
  void handleInput(Input input) override;
  void update() override { };
  void draw() override;
};