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
  if (!vbo_)
    return;
  if (ref_count_) {
    if (*ref_count_--)
      return;
    delete ref_count_;
  }
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}

void VertexArray::Bind() const {
  glBindVertexArray(vao_);
}

void VertexArray::UnBind() const {
  glBindVertexArray(0);
}

VertexArray::VertexArray(const VertexArray& other) {
  this->operator=(other);
}

VertexArray::VertexArray(VertexArray&& other) {
  this->operator=(std::move(other));
}

VertexArray& VertexArray::operator=(const VertexArray& other) {
  this->~VertexArray();
  vao_ = other.vao_;
  vbo_ = other.vbo_;
  if (!other.ref_count_)
    other.ref_count_ = new int(1);
  ref_count_ = other.ref_count_;
  *ref_count_ += 1;

  return *this;
}

VertexArray& VertexArray::operator=(VertexArray&& other) {
  std::swap(vbo_, other.vbo_);
  std::swap(vao_, other.vao_);
  std::swap(size_, other.size_);
  std::swap(ref_count_, other.ref_count_);
  return *this;
}

}  // namespace smk.
