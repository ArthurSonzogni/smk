// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "smk/Color.hpp"

namespace smk {

/// Color namespace
namespace Color {

/// @brief Build a color from its RGBA components components.
/// This is equivalent to calling the glm::vec4 constructor.
/// @param red: The red component in [0,1]
/// @param blue: The blue component in [0,1]
/// @param green: The green component in [0,1]
/// @param alpha: The alpha component in [0,1]
glm::vec4 RGBA(float red, float green, float blue, float alpha) {
  return {red, green, blue, alpha};
}

/// @brief Build an opaque color from its RGB components components.
/// @param red: The red component in [0,1]
/// @param blue: The blue component in [0,1]
/// @param green: The green component in [0,1]
glm::vec4 RGB(float red, float green, float blue) {
  return {red, green, blue, 1.f};
}

// clang-format off
glm::vec4 White       = glm::vec4(1.f, 1.f, 1.f, 1.f); ///< White
glm::vec4 Black       = glm::vec4(0.f, 0.f, 0.f, 1.f); ///< Black
glm::vec4 Red         = glm::vec4(1.f, 0.f, 0.f, 1.f); ///< Red
glm::vec4 Green       = glm::vec4(0.f, 1.f, 0.f, 1.f); ///< Green
glm::vec4 Blue        = glm::vec4(0.f, 0.f, 1.f, 1.f); ///< Blue
glm::vec4 Yellow      = glm::vec4(1.f, 1.f, 0.f, 1.f); ///< Yellow
glm::vec4 Magenta     = glm::vec4(1.f, 0.f, 1.f, 1.f); ///< Magenta
glm::vec4 Cyan        = glm::vec4(0.f, 1.f, 1.f, 1.f); ///< Cyan
glm::vec4 Transparent = glm::vec4(0.f, 0.f, 0.f, 0.f); ///< Transparent
// clang-format on

}  // namespace Color
}  // namespace smk
