#pragma once
#include "miniaudio.h"

#include <map>
#include <sol/sol.hpp>
#include <string>

class AudioManager
{
private:
  static ma_engine                          engine_;
  static std::map<std::string, std::string> sound_paths_;
  static ma_sound                           background_music_;
  static bool                               background_music_initialized_;
  static sol::state                         lua_;

public:
  static void initSounds();
  static void destroySounds();
  static void playBackgroundMusic();
  static void stopBackgroundMusic();
  static void playSound(const std::string& sound_name);
  static void stopSound(const std::string& sound_name);
};