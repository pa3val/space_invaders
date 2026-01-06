#include "menu_state.hpp"

MenuState::MenuState()
{
  getFilesInDirectory("levels");
}

void MenuState::getFilesInDirectory(const std::filesystem::path& path)
{
  std::filesystem::directory_iterator it(path);
  for (const auto& entry : it)
  {
    if (entry.is_regular_file() && entry.path().extension() == ".txt")
    {
      level_files_.push_back(entry.path().stem().string());
    }
  }
}

void MenuState::draw()
{
  std::string space_inviders = "SPACE INVIDERS";
  Renderer::drawText(INFO_BAR_WIDTH / 2 - space_inviders.length() / 2, 1, space_inviders, "SELECTED_TEXT_COLOR", Renderer::WindowType::INFO_BAR);
  for (std::size_t i = 0; i < buttons_text_.size(); ++i)
  {
    if (i == selected_item_)
      Renderer::drawText(PLAYFIELD_WIDTH / 2 - buttons_text_[selected_item_].length() / 2, selected_item_ + PLAYFIELD_HEIGHT / 2, buttons_text_[selected_item_], "SELECTED_TEXT_COLOR", Renderer::WindowType::PLAYFIELD);
    else
      Renderer::drawText(PLAYFIELD_WIDTH / 2 - buttons_text_[i].length() / 2, i + PLAYFIELD_HEIGHT / 2, buttons_text_[i], "TEXT_COLOR", Renderer::WindowType::PLAYFIELD);
  }
  Renderer::drawText(PLAYFIELD_WIDTH / 2 + buttons_text_[0].length() / 2 + 3, PLAYFIELD_HEIGHT / 2, '<' + level_files_[selected_level_] + '>', "TEXT_COLOR", Renderer::WindowType::PLAYFIELD);
}

void MenuState::handleInput(Input input)
{
  switch (input)
  {
  case Input::MOVE_DOWN:
    if (selected_item_ == buttons_text_.size() - 1)
      selected_item_ = 0;
    else
      ++selected_item_;
    break;
  case Input::MOVE_UP:
    if (selected_item_ == 0)
      selected_item_ = buttons_text_.size() - 1;
    else
      --selected_item_;
    break;
  case Input::MOVE_RIGHT:
    if (selected_item_ == 0 && selected_level_ == level_files_.size() - 1)
      selected_level_ = 0;
    else if (selected_item_ == 0)
      ++selected_level_;
    break;
  case Input::MOVE_LEFT:
    if (selected_item_ == 0 && selected_level_ == 0)
      selected_level_ = level_files_.size() - 1;
    else if (selected_item_ == 0)
      --selected_level_;
    break;

  case Input::SELECT:
    if (selected_item_ == 0)
    {
      SignalManager::setSignal(Signals::CHANGE_TO_LEVEL);
      LevelManager::setLevelFile(level_files_[selected_level_]);
    }
    else if (selected_item_ == 1)
      SignalManager::setSignal(Signals::EXIT);

    break;
  default:
    break;
  }
}