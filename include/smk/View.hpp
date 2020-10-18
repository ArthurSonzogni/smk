// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VIEW_HPP
#define SMK_VIEW_HPP

#include <glm/glm.hpp>

namespace smk {

/// Represent the area in the game to be drawn on the screen. To preserve the
/// screen ratio, the view ratio must be the same.
class View {
 public:
  void SetCenter(float x, float y);
  void SetCenter(const glm::vec2& center);
  void SetSize(float width, float height);
  void SetSize(const glm::vec2& size);

  float Left() const { return x_ - width_ / 2; };     /// <
  float Right() const { return x_ + width_ / 2; };    /// <
  float Top() const { return y_ - height_ / 2; };     /// <
  float Bottom() const { return y_ + height_ / 2; };  /// <

 public:
  float x_ = 0.f;
  float y_ = 0.f;
  float width_ = 0.f;
  float height_ = 0.f;
};

}  // namespace smk

#endif /* end of include guard: SMK_VIEW_HPP */
