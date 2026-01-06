#include "game_over_state.hpp"

GameOverState::GameOverState(int score)
    : score_(score)
{
}

void GameOverState::handleInput(Input input)
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
  case Input::SELECT:
    if (selected_item_ == 0)
      SignalManager::setSignal(Signals::CHANGE_TO_LEVEL);
    else if (selected_item_ == 1)
      SignalManager::setSignal(Signals::CHANGE_TO_MENU);
    break;
  default:
    break;
  }
}

void GameOverState::draw()
{
  std::string game_over_text = "GAME OVER";
  Renderer::drawText(
      INFO_BAR_WIDTH / 2 - game_over_text.length() / 2,
      1,
      game_over_text,
      "SELECTED_TEXT_COLOR",
      Renderer::WindowType::INFO_BAR);
  std::string score_text = "Score: " + std::to_string(score_);
  Renderer::drawText(
      PLAYFIELD_WIDTH / 2 - score_text.length() / 2,
      1,
      score_text,
      "TEXT_COLOR", Renderer::WindowType::PLAYFIELD);
  for (std::size_t i = 0; i < buttons_text_.size(); ++i)
  {
    if (i == selected_item_)
    {
      Renderer::drawText(PLAYFIELD_WIDTH / 2 - buttons_text_[i].length() / 2, i + PLAYFIELD_HEIGHT / 2, buttons_text_[i], "SELECTED_TEXT_COLOR", Renderer::WindowType::PLAYFIELD);
    }
    else
    {
      Renderer::drawText(PLAYFIELD_WIDTH / 2 - buttons_text_[i].length() / 2, i + PLAYFIELD_HEIGHT / 2, buttons_text_[i], "TEXT_COLOR", Renderer::WindowType::PLAYFIELD);
    }
  }
}