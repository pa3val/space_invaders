#define MINIAUDIO_IMPLEMENTATION
#include "audio_manager.hpp"

ma_engine                          AudioManager::engine_;
std::map<std::string, std::string> AudioManager::sound_paths_;
ma_sound                           AudioManager::background_music_;
bool                               AudioManager::background_music_initialized_ = false;
sol::state                         AudioManager::lua_;

void AudioManager::initSounds()
{
  ma_engine_init(NULL, &engine_);
  ma_engine_start(&engine_);
  lua_.open_libraries(sol::lib::base, sol::lib::package);
  lua_.script_file("global_config.lua");

  sol::table sounds = lua_["sounds"];

  for (auto& [key, value] : sounds)
  {
    sound_paths_[key.as<std::string>()] = value.as<std::string>();
  }
}

void AudioManager::playBackgroundMusic()
{
  if (background_music_initialized_)
  {
    ma_sound_uninit(&background_music_); // очистить предыдущий
  }
  ma_sound_init_from_file(&engine_, sound_paths_["BACKGROUND_MUSIC"].c_str(), 0, NULL, NULL, &background_music_);
  ma_sound_set_looping(&background_music_, MA_TRUE);
  ma_sound_start(&background_music_);
  background_music_initialized_ = true;
}

void AudioManager::stopBackgroundMusic()
{
  if (background_music_initialized_)
  {
    ma_sound_stop(&background_music_);
    ma_sound_uninit(&background_music_);
    background_music_initialized_ = false;
  }
}

void AudioManager::destroySounds()
{

  ma_engine_uninit(&engine_);
}

void AudioManager::playSound(const std::string& sound_name)
{
  ma_engine_play_sound(&engine_, sound_paths_[sound_name].c_str(), NULL);
}

void AudioManager::stopSound(const std::string& sound_name)
{
  // ma_engine_stop_sound(&engine_, sound_paths_[sound_name].c_str());
}