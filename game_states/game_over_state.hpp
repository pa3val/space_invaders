#pragma once

#include "constants.hpp"
#include "game_state.hpp"
#include "renderer.hpp"

#include <array>
#include <string>

class GameOverState : public GameState
{
private:
  int                        score_;
  std::size_t                selected_item_ = 0;
  std::array<std::string, 2> buttons_text_  = {
    "Restart",
    "To Menu"
  };

public:
  GameOverState(int score = 0);
  void handleInput(Input input) override;
  void update() override { };
  void draw() override;
};