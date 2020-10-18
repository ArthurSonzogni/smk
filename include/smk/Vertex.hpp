// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VERTEX_HPP
#define SMK_VERTEX_HPP

#include <glm/glm.hpp>

namespace smk {

/// The vertex structure suitable for a 2D shader.
struct Vertex2D {
  glm::vec2 space_position = {0.f, 0.f};
  glm::vec2 texture_position = {0.f, 0.f};

  static void Bind();
};

/// The vertex structure suitable for a 2D shader.
struct Vertex3D {
  glm::vec3 space_position = {0.f, 0.f, 0.f};
  glm::vec3 normal = {0.f, 0.f, 0.f};
  glm::vec2 texture_position = {0.f, 0.f};

  static void Bind();
};

using Vertex = Vertex2D;

}  // namespace smk.

#endif /* end of include guard: SMK_VERTEX_HPP */
