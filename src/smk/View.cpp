// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/View.hpp>

namespace smk {

/// @brief Set the center position of the in-game view.
/// param x The center of the view along the horizontal axis.
/// param y The center of the view along the vertical axis.
void View::SetCenter(float x, float y) {
  x_ = x;
  y_ = y;
}

/// @brief Set the center position of the in-game view.
/// param center The center of the view.
void View::SetCenter(const glm::vec2& center) {
  SetCenter(center.x, center.y);
}

/// @brief Set the size of the in-game view.
/// param width The size of the view along the horizontal axis.
/// param height The size of the view along the vertical axis.
void View::SetSize(float width, float height) {
  width_ = width;
  height_ = height;
}

/// @brief Set the size of the in-game view.
/// param center The size of the view.
void View::SetSize(const glm::vec2& size) {
  SetSize(size.x, size.y);
}

}  // namespace smk
