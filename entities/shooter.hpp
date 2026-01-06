#pragma once
#include "bullet.hpp"
#include "entity.hpp"

#include <memory>


class Shooter : public Entity
{
private:
  unsigned short reload_frame_delay_         = 5;
  unsigned short current_reload_frame_delay_ = 0;

  std::vector<std::vector<char>> bullet_appearance_;

public:
  Shooter();
  virtual ~Shooter()                            = default;
  virtual std::unique_ptr<Bullet>       shoot() = 0;
  bool                                  canShoot() const;
  void                                  resetReloadFrameDelay();
  void                                  updateReloadFrameDelay();
  void                                  setReloadFrameDelay(unsigned short reload_frame_delay);
  void                                  setBulletAppearance(const std::vector<std::vector<char>>& bullet_appearance);
  const std::vector<std::vector<char>>& getBulletAppearance() const;
};