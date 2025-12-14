#pragma once
#include "bullet.hpp"
#include "collision_manager.hpp"
#include "constants.hpp"
#include "game_state.hpp"
#include "player.hpp"
#include "signal_manager.hpp"
#include "renderer.hpp"

#include <memory>
#include <vector>

class LevelState : public GameState
{
private:
  std::vector<std::unique_ptr<Bullet>> bullet_pool_;
  Player                               player_;
  CollisionManager                     collision_manager_;

public:
  LevelState();
  void handleInput(Input input) override;
  void update() override { };
  void draw() override;
  void drawField();
};