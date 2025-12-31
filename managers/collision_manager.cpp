#include "collision_manager.hpp"

#include "constants.hpp"

bool CollisionManager::checkBounderCollision(const Entity& entity, short delta_x, short delta_y)
{
  int new_pos_x = entity.getPosX() + static_cast<int>(delta_x);
  int new_pos_y = entity.getPosY() + static_cast<int>(delta_y);

  if (new_pos_x < static_cast<int>(BORDER_SIZE) && delta_x < 0)
    return true;
  else if (new_pos_x + static_cast<int>(entity.getWidth())
               > PLAYFIELD_WIDTH - static_cast<int>(BORDER_SIZE)
           && delta_x > 0)
    return true;

  if (new_pos_y < static_cast<int>(BORDER_SIZE) && delta_y < 0)
    return true;
  else if (new_pos_y + static_cast<int>(entity.getHeight())
               > PLAYFIELD_HEIGHT - static_cast<int>(BORDER_SIZE)
           && delta_y > 0)
    return true;

  return false;
}

bool CollisionManager::checkCollision(const Entity& entity1, const Entity& entity2)
{
  int x1 = entity1.getPosX();
  int y1 = entity1.getPosY();
  int x2 = entity2.getPosX();
  int y2 = entity2.getPosY();

  bool overlapX = (x1 < x2 + static_cast<int>(entity2.getWidth()))
                  && (x1 + static_cast<int>(entity1.getWidth()) > x2);

  bool overlapY = (y1 < y2 + static_cast<int>(entity2.getHeight()))
                  && (y1 + static_cast<int>(entity1.getHeight()) > y2);

  return overlapX && overlapY;
}