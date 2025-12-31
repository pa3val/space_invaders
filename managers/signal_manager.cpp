#include "signal_manager.hpp"

Signals                  SignalManager::signal_     = Signals::NONE;
SignalManager::DrawFlags SignalManager::draw_flags_ = SignalManager::DrawFlags::DRAW_NONE;