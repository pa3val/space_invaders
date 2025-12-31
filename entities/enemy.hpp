#pragma once
#include "damageable.hpp"
#include "entity.hpp"

class Enemy : public Entity, public Damageable
{
private:
  unsigned long score_ = 0;

public:
  Enemy();
  Enemy(
      int                                   pos_x,
      int                                   pos_y,
      int                                   health,
      unsigned long                         score,
      const std::vector<std::vector<char>>& appearance);
  void          setScore(unsigned long score) { score_ = score; }
  unsigned long getScore() const { return score_; }
};