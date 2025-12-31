#pragma once
#include "constants.hpp"
#include "enemy.hpp"
#include "player.hpp"

#include <fstream>
#include <memory>
#include <sol/sol.hpp>
#include <vector>

class LevelManager
{
private:
  static std::string                         level_file_;
  static std::vector<std::unique_ptr<Enemy>> enemy_pool_;
  static Player                              player_;
  static sol::state                          lua;

public:
  static void readLevelFile();
  static void saveLevelFile();
  static void setLevelFile(const std::string& file_name)
  {
    level_file_ = file_name;
  }
  static std::string                         getLevelFile() { return level_file_; }
  static std::vector<std::unique_ptr<Enemy>> takeEnemyPool() { return std::move(enemy_pool_); }
  static Player                              takePlayer() { return player_; }
};