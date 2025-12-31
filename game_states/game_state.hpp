#pragma once
#include "constants.hpp"
class GameState
{

public:
  GameState() { };
  virtual ~GameState() = default;
  virtual void handleInput(Input input) { };
  virtual void update() { };
  virtual void draw() { };
};