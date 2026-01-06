#pragma once
#include "bullet.hpp"
#include "damageable.hpp"
#include "shooter.hpp"

#include <memory>

class Player : public Shooter, public Damageable
{
public:
  Player();
  virtual ~Player() = default;
  std::unique_ptr<Bullet> shoot() override;
};