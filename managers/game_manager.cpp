#include "game_manager.hpp"

GameManager::GameManager()
{
  initScreen();
  initColors();
  state_ = std::make_unique<MenuState>();
}

void GameManager::initScreen()
{
  printf("\033[8;%d;%dt", SCREEN_HEIGHT, SCREEN_WIDTH);
  fflush(stdout);
  initscr();
  resizeterm(SCREEN_HEIGHT, SCREEN_WIDTH);
  Renderer::init_info_bar();
  Renderer::init_playfield();
  start_color();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
  raw();
  noecho();
}

void GameManager::initColors()
{
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
  init_pair(6, COLOR_BLACK, COLOR_WHITE);
}

void GameManager::runGame()
{
  while (SignalManager::getSignal() != Signals::EXIT)
  {
    handleSignal();
    Input input = InputManager::getInputState();
    state_->handleInput(input);
    state_->update();
    Renderer::reset_cleared_flags();
    state_->draw();
    if ((SignalManager::getDrawFlags() & SignalManager::DrawFlags::DRAW_INFO_BAR)
        != SignalManager::DrawFlags::DRAW_NONE)
      Renderer::refresh_window(Renderer::WindowType::INFO_BAR);
    if ((SignalManager::getDrawFlags() & SignalManager::DrawFlags::DRAW_PLAYFIELD)
        != SignalManager::DrawFlags::DRAW_NONE)
      Renderer::refresh_window(Renderer::WindowType::PLAYFIELD);
    Renderer::update_screen();
    SignalManager::clearDrawFlags();
    Renderer::wait(1000 / 30);
  }
  Renderer::exit_game();
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
  case Signals::GAME_OVER:
    state_ = std::make_unique<GameOverState>(dynamic_cast<LevelState*>(state_.get())->getScore());
    SignalManager::setSignal(Signals::NONE);
    break;
  default:
    break;
  }
}