#pragma once
#include "audio_manager.hpp"
#include "bullet.hpp"
#include "collision_manager.hpp"
#include "constants.hpp"
#include "enemy.hpp"
#include "game_state.hpp"
#include "level_manager.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "signal_manager.hpp"

#include <algorithm>
#include <filesystem>
#include <memory>
#include <random>
#include <vector>

class LevelState : public GameState
{
private:
  std::vector<std::unique_ptr<Bullet>>  bullet_pool_;
  std::vector<std::unique_ptr<Enemy>>   enemy_pool_;
  Player                                player_;
  short                                 enemy_direction_x_  = 1;
  unsigned long                         score_              = 0;
  int                                   enemy_shoot_chance_ = 5;
  SignalManager::DrawFlags              draw_flags_         = SignalManager::DrawFlags::DRAW_NONE;
  std::mt19937                          rng_ { std::random_device {}() };
  std::uniform_int_distribution<size_t> chance { 0, 100 };

public:
  LevelState();
  void          handleInput(Input input) override;
  void          update() override;
  void          moveEnemies();
  void          shootEnemies();
  void          draw() override;
  void          drawBullets();
  void          drawEnemies();
  unsigned long getScore() const { return score_; }
};
