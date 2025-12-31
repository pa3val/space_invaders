#pragma once
#include "constants.hpp"

class SignalManager
{
public:
  enum class DrawFlags : unsigned short
  {
    DRAW_NONE      = 0,
    DRAW_PLAYFIELD = 1 << 0,
    DRAW_INFO_BAR  = 1 << 1,
  };

private:
  static Signals   signal_;
  static DrawFlags draw_flags_;

public:
  static void      setSignal(Signals signal) { signal_ = signal; }
  static Signals   getSignal() { return signal_; }
  static void      setDrawFlag(DrawFlags flag);
  static DrawFlags getDrawFlags() { return draw_flags_; }
  static void      clearDrawFlags() { draw_flags_ = DrawFlags::DRAW_NONE; }
};

inline SignalManager::DrawFlags operator|(SignalManager::DrawFlags a, SignalManager::DrawFlags b)
{
  return static_cast<SignalManager::DrawFlags>(static_cast<unsigned short>(a) | static_cast<unsigned short>(b));
}
inline SignalManager::DrawFlags& operator|=(SignalManager::DrawFlags& first, SignalManager::DrawFlags second)
{
  first = first | second;
  return first;
}
inline SignalManager::DrawFlags operator&(SignalManager::DrawFlags a, SignalManager::DrawFlags b)
{
  return static_cast<SignalManager::DrawFlags>(static_cast<unsigned short>(a) & static_cast<unsigned short>(b));
}
inline SignalManager::DrawFlags& operator&=(SignalManager::DrawFlags& first, SignalManager::DrawFlags second)
{
  first = first & second;
  return first;
}

inline void SignalManager::setDrawFlag(SignalManager::DrawFlags flag) { draw_flags_ |= flag; }
