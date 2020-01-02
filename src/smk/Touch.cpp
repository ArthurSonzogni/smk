// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Touch.hpp>

namespace smk {

glm::vec2 Touch::position() const {
  return data_points.back().position;
}

}  // namespace smk
