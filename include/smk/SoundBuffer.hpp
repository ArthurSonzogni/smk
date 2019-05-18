// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SOUND_BUFFER_HPP
#define SMK_SOUND_BUFFER_HPP

#include <string>

namespace smk {
class Sound;
class SoundBuffer {
 public:
  // Please make sure to init OpenAL in main() by creating a smk::Audio.
  SoundBuffer();  // Empty sound buffer
  SoundBuffer(const std::string filename);

  ~SoundBuffer();

  void Play();

  // --- Move only resource ----------------------------------------------------
  SoundBuffer(SoundBuffer&&);
  SoundBuffer(const SoundBuffer&) = delete;
  void operator=(SoundBuffer&&);
  void operator=(const SoundBuffer&) = delete;
  // ---------------------------------------------------------------------------

  unsigned int buffer = 0;
};
}  // namespace smk

#endif /* end of include guard: SMK_SOUND_BUFFER_HPP */
