#include "damageable.hpp"

void Damageable::takeDamage(unsigned int damage)
{
  if (getHealth() <= damage)
    setHealth(0);
  else
    setHealth(getHealth() - damage);
}