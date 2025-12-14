#pragma once
#include "constants.hpp"

class SignalManager
{
private:
  static Signals signal_;

public:
  static void    setSignal(Signals signal) { signal_ = signal; }
  static Signals getSignal() { return signal_; }
};