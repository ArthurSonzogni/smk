// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SOUND_HPP
#define SMK_SOUND_HPP

#include <smk/SoundBuffer.hpp>

namespace smk {

/// @example sound.cpp

/// @brief Represent a sound being played.
/// @see SoundBuffer
///
/// Example
/// -------
/// ~~~cpp
/// // Load a sound file.
/// auto sound_buffer = smk::SoundBuffer(asset::water_mp3);
///
/// // Create a sound source.
/// auto sound = smk::Sound(sound_buffer);
///
/// // Start playing.
/// sound.Play()
/// ~~~
///
/// Please make sure to init OpenAL in main() by creating a smk::Audio.
class Sound {
 public:
  Sound();
  Sound(const SoundBuffer& buffer);
  ~Sound();

  void Play();
  void Stop();
  void SetLoop(bool looping);
  bool IsPlaying() const;

  // The gain applied to the source. Default is 1.
  void SetVolume(float volume);

  // -- Move-only resource ---
  Sound(Sound&&) noexcept;
  Sound(const Sound&) = delete;
  Sound& operator=(Sound&&) noexcept;
  Sound& operator=(const Sound&) = delete;

 private:
  const SoundBuffer* buffer_ = nullptr;
  unsigned int source_ = 0;
  bool is_playing_ = false;

  void EnsureSourceIsCreated();
};

}  // namespace smk

#endif /* end of include guard: SMK_SOUND_HPP */
