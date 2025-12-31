#include "level_manager.hpp"

std::vector<std::unique_ptr<Enemy>> LevelManager::enemy_pool_ = {};
Player                              LevelManager::player_     = Player();
std::string                         LevelManager::level_file_ = "level_1";
sol::state                          LevelManager::lua         = sol::state();

void LevelManager::readLevelFile()
{
  enemy_pool_.clear();
  player_ = Player();
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.script_file("config.lua");

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
      player_ = Player(
          i,
          j,
          lua["global_states"]["player"]["health"].get<int>(),
          lua["global_states"]["player"]["appearance"].get<std::vector<std::vector<char>>>());
      break;
    case 'E':
      enemy_pool_.push_back(
          std::make_unique<Enemy>(
              Enemy(
                  i,
                  j,
                  lua["global_states"]["basic_enemy"]["health"].get<int>(),
                  lua["global_states"]["basic_enemy"]["score"].get<unsigned long>(),
                  lua["global_states"]["basic_enemy"]["appearance"].get<std::vector<std::vector<char>>>())));
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