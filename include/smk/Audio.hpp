// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_AUDIO_HPP
#define SMK_AUDIO_HPP

namespace smk {

// Initialize OpenAL.
class Audio {
 public:
  Audio() { IncreaseRef();}
  ~Audio() { DecreaseRef(); }

  Audio(const Audio&) { IncreaseRef(); }
  Audio(Audio&&) { IncreaseRef(); }

 private:
  void IncreaseRef();
  void DecreaseRef();
};

}  // namespace smk

#endif /* end of include guard: SMK_AUDIO_HPP */
