// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_DRAWABLE
#define SMK_DRAWABLE

#include <smk/RenderState.hpp>

namespace smk {
class RenderTarget;

/// Interface for class that can be draw to a smk::RenderTarget.
class Drawable {
 public:
  /// Draw the object on a RenderTarget.
  /// @param target: A RenderTarget to be drawn on.
  /// @param state: The RenderState to derive from.
  virtual void Draw(RenderTarget& target, RenderState state) const = 0;
};

}  // namespace smk

#endif /* end of include guard: SMK_DRAWABLE */
