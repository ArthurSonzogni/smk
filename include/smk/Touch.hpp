// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_TOUCH_HPP
#define SMK_TOUCH_HPP

#include <glm/glm.hpp>
#include <vector>

namespace smk {

/// @example touch.cpp

struct TouchDataPoint {
  glm::vec2 position = {0, 0};
  float time = 0.f;
};

struct Touch {
  int finger_id = 0;
  std::vector<TouchDataPoint> data_points;

  glm::vec2 position() const;
};

}  // namespace smk

#endif /* end of include guard: SMK_TOUCH_HPP */
