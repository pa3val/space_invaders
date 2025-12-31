#include "enemy.hpp"

Enemy::Enemy()
    : Entity()
{
  const std::vector<std::vector<char>> appearance = {
    { ' ', '/', '\\', ' ' },
    { '<', 'O', 'O', '>' },
    { ' ', '\\', '/', ' ' }
  };
  setAppearance(appearance);
  setWidth(appearance[0].size());
  setHeight(appearance.size());
  setHealth(1);
  setScore(0);
}

Enemy::Enemy(
    int                                   pos_x,
    int                                   pos_y,
    int                                   health,
    unsigned long                         score,
    const std::vector<std::vector<char>>& appearance)
    : Entity()
{
  setAppearance(appearance);
  setWidth(appearance[0].size());
  setHeight(appearance.size());
  setHealth(health);
  setScore(score);
  setPosX(pos_x);
  setPosY(pos_y);
}