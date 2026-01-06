#include "game_manager.hpp"

GameManager::GameManager()
{
  Renderer::initScreen();
  Renderer::initColorMap();
  AudioManager::initSounds();
  state_ = std::make_unique<MenuState>();
}

void GameManager::runGame()
{
  while (SignalManager::getSignal() != Signals::EXIT)
  {
    handleSignal();
    Input input = InputManager::getInputState();
    state_->handleInput(input);
    state_->update();
    Renderer::resetFlags();
    state_->draw();
    if ((SignalManager::getDrawFlags() & SignalManager::DrawFlags::DRAW_INFO_BAR)
        != SignalManager::DrawFlags::DRAW_NONE)
      Renderer::refreshWindow(Renderer::WindowType::INFO_BAR);
    if ((SignalManager::getDrawFlags() & SignalManager::DrawFlags::DRAW_PLAYFIELD)
        != SignalManager::DrawFlags::DRAW_NONE)
      Renderer::refreshWindow(Renderer::WindowType::PLAYFIELD);
    Renderer::updateScreen();
    SignalManager::clearDrawFlags();
    Renderer::wait(1000 / 30);
  }
  AudioManager::destroySounds();
  Renderer::exitGame();
}

void GameManager::handleSignal()
{
  switch (SignalManager::getSignal())
  {
  case Signals::CHANGE_TO_LEVEL:
    AudioManager::stopBackgroundMusic();
    state_ = std::make_unique<LevelState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  case Signals::CHANGE_TO_MENU:
    AudioManager::stopBackgroundMusic();
    state_ = std::make_unique<MenuState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  case Signals::GAME_OVER:
  {
    AudioManager::stopBackgroundMusic();
    unsigned long score = 0;
    if (auto* level = dynamic_cast<LevelState*>(state_.get()))
    {
      score = level->getScore();
    }
    state_ = std::make_unique<GameOverState>(score);
    SignalManager::setSignal(Signals::NONE);
    break;
  }
  default:
    break;
  }
}