#pragma once
#include "entity.hpp"

#include <memory>

class CollisionManager
{
public:
  CollisionManager();
  bool checkBounderCollision(const Entity& entity, short delta_x, short delta_y);
};