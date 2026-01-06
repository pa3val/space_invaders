#include "level_manager.hpp"

std::vector<std::unique_ptr<Enemy>> LevelManager::enemy_pool_         = {};
Player                              LevelManager::player_             = Player();
Enemy                               LevelManager::enemy_              = Enemy();
std::string                         LevelManager::level_file_         = "level_1";
int                                 LevelManager::enemy_shoot_chance_ = 5;
sol::state                          LevelManager::lua_;

void LevelManager::readLevelFile()
{
  enemy_pool_.clear();
  lua_.open_libraries(sol::lib::base, sol::lib::package);
  lua_.script_file("global_config.lua");
  setupPlayer();
  setupEnemy();
  enemy_shoot_chance_ = lua_["global_states"]["enemies"]["enemy_shoot_chance"].get<int>();

  std::ifstream file("levels/" + level_file_ + ".txt");
  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open level file " + level_file_ + ".txt");
  }

  int  i = 0, j = 0;
  char ch;
  while (file.get(ch))
  {
    switch (ch)
    {
    case 'P':
      player_.setPosX(i);
      player_.setPosY(j);
      break;
    case 'E':
      enemy_.setPosX(i);
      enemy_.setPosY(j);
      enemy_pool_.push_back(
          std::make_unique<Enemy>(
              enemy_));
      break;
    case '\n':
      ++j;
      i = 0;
      continue;
    default:
      break;
    }
    ++i;
  }
  file.close();
}

void LevelManager::setupPlayer()
{
  sol::table player_states = lua_["global_states"]["player"];
  player_.setHealth(player_states["health"].get<unsigned int>());
  player_.setReloadFrameDelay(player_states["player_shoot_delay"].get<unsigned short>());
  player_.setAppearance(player_states["player_appearance"].get<std::vector<std::vector<char>>>());
  player_.setWidth(player_.getAppearance()[0].size());
  player_.setHeight(player_.getAppearance().size());
  player_.setBulletAppearance(player_states["player_bullet_appearance"].get<std::vector<std::vector<char>>>());
}
void LevelManager::setupEnemy()
{
  sol::table enemy_states = lua_["global_states"]["enemies"]["basic_enemy"];
  enemy_.setHealth(enemy_states["health"].get<unsigned int>());
  enemy_.setEnemyMovementDelay(enemy_states["enemy_movement_delay"].get<unsigned short>());
  enemy_.setReloadFrameDelay(enemy_states["enemy_shoot_delay"].get<unsigned short>());
  enemy_.setAppearance(enemy_states["appearance"].get<std::vector<std::vector<char>>>());
  enemy_.setWidth(enemy_.getAppearance()[0].size());
  enemy_.setHeight(enemy_.getAppearance().size());
  enemy_.setBulletAppearance(enemy_states["enemy_bullet_appearance"].get<std::vector<std::vector<char>>>());
  enemy_.setScore(enemy_states["score"].get<unsigned long>());
}
