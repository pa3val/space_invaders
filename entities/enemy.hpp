#pragma once
#include "bullet.hpp"
#include "damageable.hpp"
#include "shooter.hpp"

#include <memory>

class Enemy : public Shooter, public Damageable
{
private:
  unsigned long  score_                        = 0;
  unsigned short enemy_movement_delay_         = 50;
  unsigned short current_enemy_movement_delay_ = 0;

public:
  Enemy();
  virtual ~Enemy() = default;
  void           setScore(unsigned long score) { score_ = score; }
  unsigned long  getScore() const { return score_; }
  void           setEnemyMovementDelay(unsigned short enemy_movement_delay) { enemy_movement_delay_ = enemy_movement_delay; }
  unsigned short getEnemyMovementDelay() const { return enemy_movement_delay_; }
  unsigned short getCurrentEnemyMovementDelay() const { return current_enemy_movement_delay_; }
  void           updateCurrentEnemyMovementDelay()
  {
    if (current_enemy_movement_delay_ > 0)
      --current_enemy_movement_delay_;
  }
  void                    resetCurrentEnemyMovementDelay() { current_enemy_movement_delay_ = enemy_movement_delay_; }
  std::unique_ptr<Bullet> shoot() override;
};