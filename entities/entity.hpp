#pragma once
#include "constants.hpp"

#include <curses.h>
#include <vector>

class Entity
{
private:
  unsigned int                   width_ = 0, height_ = 0;
  int                            pos_x_ = 0, pos_y_ = 0;
  std::vector<std::vector<char>> appearance_;

public:
  Entity();
  virtual ~Entity() = default;
  virtual void                          update(short delta_x, short delta_y);
  int                                   getPosX() const { return pos_x_; }
  int                                   getPosY() const { return pos_y_; }
  unsigned int                          getHeight() const { return height_; }
  unsigned int                          getWidth() const { return width_; }
  const std::vector<std::vector<char>>& getAppearance() const { return appearance_; }
  void                                  setPosX(int pos_x) { pos_x_ = pos_x; }
  void                                  setPosY(int pos_y) { pos_y_ = pos_y; }
  void                                  setWidth(unsigned int width) { width_ = width; }
  void                                  setHeight(unsigned int height) { height_ = height; }
  void                                  setAppearance(const std::vector<std::vector<char>>& appearance)
  {
    appearance_ = appearance;
  }
};