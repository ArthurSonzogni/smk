// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/VertexArray.hpp>

namespace smk {

VertexArray::VertexArray() = default;
VertexArray::VertexArray(const std::vector<Vertex>& array) {
  size_ = array.size();

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glBufferData(GL_ARRAY_BUFFER, array.size() * sizeof(Vertex), array.data(),
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, sizeof(Vertex::space_position) / sizeof(GL_FLOAT),
                        GL_FLOAT, false, sizeof(Vertex),
                        (void*)offsetof(Vertex, space_position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, sizeof(Vertex::texture_position) / sizeof(GL_FLOAT),
                        GL_FLOAT, false, sizeof(Vertex),
                        (void*)offsetof(Vertex, texture_position));
}

VertexArray::~VertexArray() {
  if (vbo_)
    glDeleteBuffers(1, &vbo_);
  if (vao_)
    glDeleteVertexArrays(1, &vao_);
}

void VertexArray::Bind() const {
  glBindVertexArray(vao_);
}

void VertexArray::UnBind() const {
  glBindVertexArray(0);
}

VertexArray::VertexArray(VertexArray&& other) {
  this->operator=(std::move(other));
}

void VertexArray::operator=(VertexArray&& other) {
  std::swap(vbo_, other.vbo_);
  std::swap(vao_, other.vao_);
  std::swap(size_, other.size_);
}

} // namespace smk.
