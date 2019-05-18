// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_AUDIO_HPP
#define SMK_AUDIO_HPP

namespace smk {

// Used to Initialize OpenAL. It is required to use it in the main() function.
class Audio {
 public:
  Audio();
  ~Audio();

  static bool Initialized();
};

}  // namespace smk

#endif /* end of include guard: SMK_AUDIO_HPP */
