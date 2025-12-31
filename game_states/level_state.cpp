#include "level_state.hpp"

#include "game_state.hpp"
#include "renderer.hpp"

LevelState::LevelState()
{
  lua.open_libraries(sol::lib::base, sol::lib::package);
  LevelManager::readLevelFile();
  setupLevel(LevelManager::getLevelFile());
  enemy_pool_ = LevelManager::takeEnemyPool();
  player_     = LevelManager::takePlayer();
  draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
  draw_flags_ |= SignalManager::DrawFlags::DRAW_INFO_BAR;
}

void LevelState::setupLevel(const std::string& level_file)
{
  lua.script_file("config.lua");
  enemy_movement_delay_ = lua["global_states"]["enemy_delay"].get<unsigned short>();
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
  case Input::FIRE:
    if (auto bullet = player_.shoot())
      bullet_pool_.push_back(std::move(bullet));
    break;
  case Input::EXIT:
    SignalManager::setSignal(Signals::CHANGE_TO_MENU);
    return;
  default:
    break;
  }
  if (!CollisionManager::checkBounderCollision(player_, delta_x, delta_y))
  {
    player_.update(delta_x, delta_y);
    draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
  }
}

void LevelState::update()
{
  if (enemy_pool_.empty())
  {
    SignalManager::setSignal(Signals::GAME_OVER);
    return;
  }

  for (auto& enemy : enemy_pool_)
  {
    if (CollisionManager::checkCollision(player_, *enemy))
    {
      SignalManager::setSignal(Signals::GAME_OVER);
      return;
    }
  }

  for (auto bullet = bullet_pool_.begin(); bullet != bullet_pool_.end();)
  {
    for (auto enemy = enemy_pool_.begin(); enemy != enemy_pool_.end(); ++enemy)
    {
      if (CollisionManager::checkCollision(**bullet, **enemy))
      {
        (*enemy)->takeDamage((*bullet)->getDamage());
        bullet->reset();
        break;
      }
    }
    ++bullet;
  }

  bullet_pool_.erase(
      std::remove_if(bullet_pool_.begin(), bullet_pool_.end(),
          [this](const auto& bullet)
          {
            if (!bullet)
            {
              draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
              return true;
            }
            return bullet->getPosY() < static_cast<int>(BORDER_SIZE);
          }),
      bullet_pool_.end());

  enemy_pool_.erase(
      std::remove_if(enemy_pool_.begin(), enemy_pool_.end(),
          [this](const auto& enemy)
          {
            if (!enemy->isAlive())
            {
              score_ += enemy->getScore();
              draw_flags_ |= SignalManager::DrawFlags::DRAW_INFO_BAR;
              draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;

              return true;
            }
            return false;
          }),
      enemy_pool_.end());

  for (auto& bullet : bullet_pool_)
  {
    bullet->update();
    draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
  }
  moveEnemies();
}

void LevelState::moveEnemies()
{
  ++current_enemy_movement_delay_;
  if (current_enemy_movement_delay_ >= enemy_movement_delay_)
  {
    current_enemy_movement_delay_ = 0;
    for (auto& enemy : enemy_pool_)
    {
      enemy->update(0, 1);
      draw_flags_ |= SignalManager::DrawFlags::DRAW_PLAYFIELD;
    }
  }
}

void LevelState::draw()
{
  if ((draw_flags_ & SignalManager::DrawFlags::DRAW_PLAYFIELD) != SignalManager::DrawFlags::DRAW_NONE)
  {
    Renderer::draw_entity(player_, ColorPair::PLAYER_COLOR, Renderer::WindowType::PLAYFIELD);
    drawBullets();
    drawEnemies();
  }
  if ((draw_flags_ & SignalManager::DrawFlags::DRAW_INFO_BAR) != SignalManager::DrawFlags::DRAW_NONE)
  {
    Renderer::draw_text(1, 1, "Score: " + std::to_string(score_), ColorPair::TEXT_COLOR, Renderer::WindowType::INFO_BAR);
    Renderer::draw_text(1, 2, "Health: " + std::to_string(player_.getHealth()), ColorPair::TEXT_COLOR, Renderer::WindowType::INFO_BAR);
  }
  draw_flags_ = SignalManager::DrawFlags::DRAW_NONE;
}

void LevelState::drawBullets()
{
  for (auto& bullet : bullet_pool_)
  {
    Renderer::draw_entity(*bullet, ColorPair::BULLET_COLOR, Renderer::WindowType::PLAYFIELD);
  }
}

void LevelState::drawEnemies()
{
  for (auto& enemy : enemy_pool_)
  {
    Renderer::draw_entity(*enemy, ColorPair::ENEMY_COLOR, Renderer::WindowType::PLAYFIELD);
  }
}