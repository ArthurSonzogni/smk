// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <smk/Audio.hpp>
#include <smk/Sound.hpp>

namespace smk {

void Sound::EnsureSourceIsCreated() {
  if (source_) {
    return;
  }

  if (!Audio::Initialized()) {
    static bool once = true;
    if (once) {
      std::cerr
          << "Error: smk::Audio has not been initialized. Please create a "
             "smk::Audio instance in the main() function before creating a "
             "smk::Sound"
          << std::endl;
      once = false;
    }
  }

  alGenSources(1, &source_);
}

/// @brief Create a null Sound.
Sound::Sound() = default;

/// @brief Create a sound reading data from a SoundBuffer
/// @param buffer The SoundBuffer to read the data from.
Sound::Sound(const SoundBuffer& buffer) : buffer_(&buffer) {}

Sound::~Sound() {
  Stop();
  if (source_) {
    alDeleteSources(1, &source_);
  }
}

/// @brief Start playing the sound.
void Sound::Play() {
  if (!buffer_ || !buffer_->buffer()) {
    return;
  }
  if (is_playing_) {
    Stop();
  }
  EnsureSourceIsCreated();
  alSourcei(source_, AL_BUFFER, ALint(buffer_->buffer()));
  alSourcePlay(source_);
  is_playing_ = true;
}

/// @brief Stop playing the sound.
void Sound::Stop() {
  if (!source_ || !buffer_ || !is_playing_) {
    return;
  }
  alSourceStop(source_);
  alSourcei(source_, AL_BUFFER, 0);
  is_playing_ = false;
}

/// @brief Specify whether the sound must restart when it has reached the end.
/// @param looping whether the sound must restart when it has reached the end.
void Sound::SetLoop(bool looping) {
  EnsureSourceIsCreated();
  alSourcei(source_, AL_LOOPING, looping);
}

/// @return return whether the sound is currently playing something or not.
bool Sound::IsPlaying() const {
  if (!source_) {
    return false;
  }
  ALint state = {};
  alGetSourcei(source_, AL_SOURCE_STATE, &state);
  return (state == AL_PLAYING);
}

Sound::Sound(Sound&& o) noexcept {
  operator=(std::move(o));
}

Sound& Sound::operator=(Sound&& o) noexcept {
  std::swap(buffer_, o.buffer_);
  std::swap(source_, o.source_);
  std::swap(is_playing_, o.is_playing_);
  return *this;
}

void Sound::SetVolume(float volume) {
  if (!source_) {
    return;
  }
  EnsureSourceIsCreated();
  alSourcef(source_, AL_GAIN, volume);
}

}  // namespace smk
