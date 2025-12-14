#include "collision_manager.hpp"

CollisionManager::CollisionManager()
{
}

bool CollisionManager::checkBounderCollision(const Entity& entity, short delta_x, short delta_y)
{
  int new_pos_x = entity.getPosX() + static_cast<int>(delta_x);
  int new_pos_y = entity.getPosY() + static_cast<int>(delta_y);

  if (new_pos_x < static_cast<int>(BORDER_SIZE) && delta_x < 0)
    return true;
  else if (new_pos_x + static_cast<int>(entity.getWidth())
               > WIDTH - static_cast<int>(BORDER_SIZE)
           && delta_x > 0)
    return true;

  if (new_pos_y < static_cast<int>(BORDER_SIZE) && delta_y < 0)
    return true;
  else if (new_pos_y + static_cast<int>(entity.getHeight())
           > HEIGHT - static_cast<int>(BORDER_SIZE) && delta_y > 0)
    return true;
    
  return false;
}