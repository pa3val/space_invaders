#pragma once
#include "constants.hpp"
#include "game_state.hpp"
#include "level_manager.hpp"
#include "renderer.hpp"
#include "signal_manager.hpp"

#include <array>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

class MenuState : public GameState
{
private:
  std::size_t                selected_item_  = 0;
  std::size_t                selected_level_ = 0;
  std::array<std::string, 2> buttons_text_   = {
    "Start",
    "Exit"
  };
  
  std::vector<std::string> level_files_;

  void getFilesInDirectory(const std::filesystem::path& path);

public:
  MenuState();
  void handleInput(Input input) override;
  void update() override { };
  void draw() override;
};