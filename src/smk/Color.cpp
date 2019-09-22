// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "smk/Color.hpp"

namespace smk {
namespace Color {

glm::vec4 RGBA(float red, float green, float blue, float alpha) {
  return {red, green, blue, alpha};
}

glm::vec4 RGB(float red, float green, float blue) {
  return {red, green, blue, 1.f};
}

// clang-format off
glm::vec4 White       = glm::vec4(1.f, 1.f, 1.f, 1.f);
glm::vec4 Black       = glm::vec4(0.f, 0.f, 0.f, 1.f);
glm::vec4 Red         = glm::vec4(1.f, 0.f, 0.f, 1.f);
glm::vec4 Green       = glm::vec4(0.f, 1.f, 0.f, 1.f);
glm::vec4 Blue        = glm::vec4(0.f, 0.f, 1.f, 1.f);
glm::vec4 Yellow      = glm::vec4(1.f, 1.f, 0.f, 1.f);
glm::vec4 Magenta     = glm::vec4(1.f, 0.f, 1.f, 1.f);
glm::vec4 Cyan        = glm::vec4(0.f, 1.f, 1.f, 1.f);
glm::vec4 Transparent = glm::vec4(0.f, 0.f, 0.f, 0.f);
// clang-format on

}  // namespace Color
}  // namespace smk
