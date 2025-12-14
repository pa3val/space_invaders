#include "level_state.hpp"

LevelState::LevelState()
{
}

void LevelState::handleInput(Input input)
{
  short delta_x = 0, delta_y = 0;

  switch (input)
  {
  case Input::MOVE_RIGHT:
    delta_x = 1;
    break;
  case Input::MOVE_LEFT:
    delta_x = -1;
    break;
  case Input::MOVE_UP:
    delta_y = -1;
    break;
  case Input::MOVE_DOWN:
    delta_y = 1;
    break;
  case Input::EXIT:
    SignalManager::setSignal(Signals::CHANGE_TO_MENU);
    return;
  }
  if (!collision_manager_.checkBounderCollision(player_, delta_x, delta_y))
    player_.update(delta_x, delta_y);
}

void LevelState::draw()
{
  drawField();
  std::vector<std::vector<char>> player_appearance = player_.getAppearance();
  for (int i = 0; i < player_.getHeight(); ++i)
  {
    for (int j = 0; j < player_.getWidth(); ++j)
      Renderer::draw_char(j + player_.getPosX(),
          i + player_.getPosY(),
          player_appearance[i][j],
          ColorPair::PLAYER_COLOR);
  }
}

void LevelState::drawField()
{
  for (int i = 0; i < WIDTH; ++i)
  {
    for (unsigned short j = 0; j < BORDER_SIZE; ++j)
    {
      Renderer::draw_char(i, j, '-', ColorPair::BORDER_COLOR);
      Renderer::draw_char(i, HEIGHT - 1 - j, '-', ColorPair::BORDER_COLOR);
    }
  }
  for (int i = 1; i < HEIGHT - 1; ++i)
  {
    for (unsigned short j = 0; j < BORDER_SIZE; ++j)
    {
      Renderer::draw_char(j, i, '|', ColorPair::BORDER_COLOR);
      Renderer::draw_char(WIDTH - 1 - j, i, '|', ColorPair::BORDER_COLOR);
    }
  }
}