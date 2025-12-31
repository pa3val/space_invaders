#pragma once
#include "bullet.hpp"
#include "damageable.hpp"
#include "shooter.hpp"

#include <memory>

class Player : public Shooter, public Damageable
{
public:
  Player();
  Player(int pos_x, int pos_y, int health, const std::vector<std::vector<char>>& appearance);
  std::unique_ptr<Bullet> shoot() override;
};