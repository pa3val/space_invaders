#include "enemy.hpp"

Enemy::Enemy()
    : Shooter()
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

std::unique_ptr<Bullet> Enemy::shoot()
{
  if (canShoot())
  {
    // incrementCurrentBullets();
    resetReloadFrameDelay();
    return std::make_unique<Bullet>(
        getPosX() + getWidth() / 2,
        getPosY() + getHeight(),
        1,
        "ENEMY_BULLET_COLOR",
        getBulletAppearance());
  }
  return nullptr;
}