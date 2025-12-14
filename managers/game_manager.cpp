#include "game_manager.hpp"

GameManager::GameManager()
{
  initScreen();
  initColors();
  state_    = std::make_unique<MenuState>();
}

void GameManager::initScreen()
{
  initscr();
  start_color();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
}

void GameManager::initColors()
{
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
}

void GameManager::runGame()
{
  while (SignalManager::getSignal() != Signals::EXIT)
  {
    handleSignal();
    Input input = InputManager::getInputState();
    state_->handleInput(input);
    state_->update();
    Renderer::clear_screen();
    state_->draw();
    Renderer::refresh_screen();
    Renderer::wait(50);
  }
  Renderer::exit_screen();
}

void GameManager::handleSignal()
{
  switch (SignalManager::getSignal())
  {
  case Signals::CHANGE_TO_LEVEL:
    state_ = std::make_unique<LevelState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  case Signals::CHANGE_TO_MENU:
    state_ = std::make_unique<MenuState>();
    SignalManager::setSignal(Signals::NONE);
    break;
  default:
    break;
  }
}