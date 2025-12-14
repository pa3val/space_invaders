#include "menu_state.hpp"

MenuState::MenuState()
{
  
}

void MenuState::draw()
{
  Renderer::draw_text(WIDTH / 2, 0, "SPACE INVIDERS", ColorPair::SELECTED_TEXT_COLOR);
  for (std::size_t i = 0; i < menu_text_.size(); ++i)
    Renderer::draw_text(WIDTH / 2, i + HEIGHT / 2, menu_text_[i], ColorPair::TEXT_COLOR);
  Renderer::draw_char(WIDTH / 2 - 1, selected_item_ + HEIGHT / 2, '>', ColorPair::SELECTED_TEXT_COLOR);
  Renderer::draw_text(WIDTH / 2, selected_item_ + HEIGHT / 2, menu_text_[selected_item_], ColorPair::SELECTED_TEXT_COLOR);
}

void MenuState::handleInput(Input input)
{
  switch (input)
  {
  case Input::MOVE_DOWN:
    if (selected_item_ == menu_text_.size() - 1)
      selected_item_ = 0;
    else
      ++selected_item_;
    break;
  case Input::MOVE_UP:
    if (selected_item_ == 0)
      selected_item_ = menu_text_.size() - 1;
    else
      --selected_item_;
    break;
  case Input::SELECT:
    if (selected_item_ == menu_text_.size() - 1)
      SignalManager::setSignal(Signals::EXIT);
    else if (selected_item_ == 0)
      SignalManager::setSignal(Signals::CHANGE_TO_LEVEL);
    break;
  default:
    break;
  }
}