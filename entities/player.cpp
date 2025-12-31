#include "player.hpp"

Player::Player()
    : Shooter()
{
  const std::vector<std::vector<char>> appearance = {
    { '/', '|', '|', '\\' },
    { '|', '0', '0', '|' },
    { ' ', '|', '|', ' ' }
  };
  setAppearance(appearance);
  setWidth(appearance[0].size());
  setHeight(appearance.size());
  setPosX(PLAYFIELD_WIDTH / 2);
  setPosY(PLAYFIELD_HEIGHT - BORDER_SIZE - appearance.size());
  setHealth(3);
}

Player::Player(int pos_x, int pos_y, int health, const std::vector<std::vector<char>>& appearance)
    : Shooter()
{
  setAppearance(appearance);
  setWidth(appearance[0].size());
  setHeight(appearance.size());
  setPosX(pos_x);
  setPosY(pos_y);
  setHealth(health);
}
std::unique_ptr<Bullet> Player::shoot()
{
  if (canShoot())
  {
    setShootTime(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch())
            .count());
    return std::make_unique<Bullet>(getPosX() + getWidth() / 2,
        getPosY() - 1, -1);
  }
  return nullptr;
}