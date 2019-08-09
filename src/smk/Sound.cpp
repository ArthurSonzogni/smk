// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Sound.hpp>
#include <smk/Audio.hpp>

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

namespace smk {

void Sound::EnsureSourceIsCreated() {
  if (source_)
    return;

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

Sound::Sound() {}
Sound::Sound(const SoundBuffer& buffer) : Sound() {
  SetBuffer(buffer);
}

Sound::~Sound() {
  Stop();
  if (source_)
    alDeleteSources(1, &source_);
}

void Sound::SetBuffer(const SoundBuffer& buffer) {
  if (buffer_ == &buffer)
    return;
  EnsureSourceIsCreated();
  Stop();
  buffer_ = &buffer;
}

void Sound::Play() {
  if (!source_ || !buffer_ || !buffer_->buffer)
    return;
  if (is_playing_)
    Stop();
  alSourcei(source_, AL_BUFFER, buffer_->buffer);
  alSourcePlay(source_);
  is_playing_ = true;
}

void Sound::Stop() {
  if (!source_ || !buffer_ || !is_playing_)
    return;
  alSourceStop(source_);
  alSourcei(source_, AL_BUFFER, 0);
  is_playing_ = false;
}

void Sound::SetLoop(bool looping) {
  EnsureSourceIsCreated();
  alSourcei(source_, AL_LOOPING, looping);
}

Sound::Sound(Sound&& o) {
  operator=(std::move(o));
}

void Sound::operator=(Sound&& o) {
  std::swap(buffer_, o.buffer_);
  std::swap(source_, o.source_);
  std::swap(is_playing_, o.is_playing_);
}

void Sound::SetVolume(float volume) {
  if (!source_)
    return;
  EnsureSourceIsCreated();
  alSourcef(source_, AL_GAIN, volume);
}

}  // namespace smk 
