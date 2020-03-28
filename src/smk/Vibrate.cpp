// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Vibrate.hpp>

#ifdef __EMSCRIPTEN__
  #include <emscripten/html5.h>
#endif

namespace smk {

#ifdef __EMSCRIPTEN__
void Vibrate(int ms) {
  emscripten_vibrate(ms);
}
#else
void Vibrate(int) {}
#endif

}  // namespace smk
