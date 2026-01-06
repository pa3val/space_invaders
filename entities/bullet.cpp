#include "bullet.hpp"

#include "entity.hpp"

Bullet::Bullet(
    int                                   p_x,
    int                                   p_y,
    short                                 direction,
    std::string                           color_name,
    const std::vector<std::vector<char>>& appearance)
    : Entity()
    , direction(direction)
    , color_name(color_name)
{
  setAppearance(appearance);
  setHeight(appearance.size());
  setWidth(appearance[0].size());
  setPosX(p_x);
  setPosY(p_y);
}

void Bullet::update()
{
  setPosY(static_cast<int>(getPosY() + direction));
}