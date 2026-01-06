#pragma once
#include "entity.hpp"

#include <string>

class Bullet : public Entity
{
private:
  short        direction = 0;
  unsigned int damage    = 1;
  std::string  color_name;

public:
  Bullet(
      int                                   p_x,
      int                                   p_y,
      short                                 direction,
      std::string                           color_name,
      const std::vector<std::vector<char>>& appearance);
  virtual ~Bullet() = default;
  void         update();
  short        getDirection() const { return direction; }
  unsigned int getDamage() const { return damage; }
  std::string  getColorName() const { return color_name; }
};