// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "smk/Color.hpp"

/// Color namespace
namespace smk::Color {

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
  return {red, green, blue, 1.F};
}

// clang-format off
const glm::vec4 White       = {1.F, 1.F, 1.F, 1.F}; ///< White
const glm::vec4 Black       = {0.F, 0.F, 0.F, 1.F}; ///< Black
const glm::vec4 Grey        = {.5f, .5f, .5f, 1.F}; ///< Grey
const glm::vec4 Red         = {1.F, 0.F, 0.F, 1.F}; ///< Red
const glm::vec4 Green       = {0.F, 1.F, 0.F, 1.F}; ///< Green
const glm::vec4 Blue        = {0.F, 0.F, 1.F, 1.F}; ///< Blue
const glm::vec4 Yellow      = {1.F, 1.F, 0.F, 1.F}; ///< Yellow
const glm::vec4 Magenta     = {1.F, 0.F, 1.F, 1.F}; ///< Magenta
const glm::vec4 Cyan        = {0.F, 1.F, 1.F, 1.F}; ///< Cyan
const glm::vec4 Transparent = {0.F, 0.F, 0.F, 0.F}; ///< Transparent
// clang-format on

}  // namespace smk::Color
