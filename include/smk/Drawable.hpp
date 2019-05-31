// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_DRAWABLE
#define SMK_DRAWABLE

#include <smk/RenderState.hpp>

namespace smk {
class Screen;

class Drawable {
 public:
  virtual void Draw(Screen& screen, RenderState state) const = 0;
};

}  // namespace smk

#endif /* end of include guard: SMK_DRAWABLE */
