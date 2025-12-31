#pragma once
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
#include <sol/sol.hpp>
#include <vector>

class LevelState : public GameState
{
private:
  sol::state                           lua;
  std::vector<std::unique_ptr<Bullet>> bullet_pool_;
  std::vector<std::unique_ptr<Enemy>>  enemy_pool_;
  Player                               player_;
  unsigned short                       enemy_movement_delay_         = 50;
  unsigned short                       current_enemy_movement_delay_ = 0;
  unsigned long                        score_                        = 0;
  SignalManager::DrawFlags             draw_flags_                   = SignalManager::DrawFlags::DRAW_NONE;

public:
  LevelState();
  void          setupLevel(const std::string& level_file);
  void          handleInput(Input input) override;
  void          update() override;
  void          moveEnemies();
  void          draw() override;
  void          drawBullets();
  void          drawEnemies();
  unsigned long getScore() const { return score_; }
};