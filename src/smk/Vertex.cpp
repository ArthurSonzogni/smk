// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "smk/Vertex.hpp"

#include <smk/OpenGL.hpp>

namespace smk {

// static
void Vertex2D::Bind() {
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, sizeof(Vertex::space_position) / sizeof(GL_FLOAT),
                        GL_FLOAT, false, sizeof(Vertex),
                        (void*)offsetof(Vertex, space_position));  // NOLINT
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, sizeof(Vertex::texture_position) / sizeof(GL_FLOAT),
                        GL_FLOAT, false, sizeof(Vertex),
                        (void*)offsetof(Vertex, texture_position));  // NOLINT
}

// static
void Vertex3D::Bind() {
  glVertexAttribPointer(0, sizeof(Vertex3D::space_position) / sizeof(GL_FLOAT),
                        GL_FLOAT, false, sizeof(Vertex3D),
                        (void*)offsetof(Vertex3D, space_position));  // NOLINT
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, sizeof(Vertex3D::normal) / sizeof(GL_FLOAT),
                        GL_FLOAT, false, sizeof(Vertex3D),
                        (void*)offsetof(Vertex3D, normal));  // NOLINT
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
      2, sizeof(Vertex3D::texture_position) / sizeof(GL_FLOAT), GL_FLOAT, false,
      sizeof(Vertex3D), (void*)offsetof(Vertex3D, texture_position));  // NOLINT
}

}  // namespace smk.
