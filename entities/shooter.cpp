#include "shooter.hpp"

Shooter::Shooter()
    : Entity()
{
}

bool Shooter::canShoot() const
{
  return current_reload_frame_delay_ == 0;
}

void Shooter::updateReloadFrameDelay()
{
  if (current_reload_frame_delay_ > 0)
    --current_reload_frame_delay_;
}

void Shooter::resetReloadFrameDelay()
{
  current_reload_frame_delay_ = reload_frame_delay_;
}

void Shooter::setReloadFrameDelay(unsigned short reload_frame_delay)
{
  reload_frame_delay_ = reload_frame_delay;
}

void Shooter::setBulletAppearance(const std::vector<std::vector<char>>& bullet_appearance)
{
  bullet_appearance_ = bullet_appearance;
}

const std::vector<std::vector<char>>& Shooter::getBulletAppearance() const
{
  return bullet_appearance_;
}