// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_AUDIO_HPP
#define SMK_AUDIO_HPP

namespace smk {

/// Used to Initialize OpenAL. It is required to use it in the main() function.
/// Coucou
///
/// ## Example 
///
/// ~~~cpp
/// int main() {
///   // Init OpenAL.
///   smk::Audio audio;
/// 
///   // Load a sound file.
///   auto sound_buffer = smk::SoundBuffer(asset::water_mp3);
/// 
///   // Create a sound source.
///   auto sound = smk::Sound(sound_buffer);
///
///   // Play the sound.
///   sound.Play();
///   
///   [...]
/// }
/// ~~~
class Audio {
 public:
  Audio();
  ~Audio();
  static bool Initialized();
};

}  // namespace smk

#endif /* end of include guard: SMK_AUDIO_HPP */
