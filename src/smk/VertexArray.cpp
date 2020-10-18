// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/VertexArray.hpp>

namespace smk {

VertexArray::VertexArray() = default;

void VertexArray::Allocate(int element_size, void* data) {
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glBufferData(GL_ARRAY_BUFFER, size_ * element_size, data, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
}

VertexArray::~VertexArray() {
  Release();
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

VertexArray::VertexArray(VertexArray&& other) noexcept {
  this->operator=(std::move(other));
}

VertexArray& VertexArray::operator=(const VertexArray& other) {
  this->~VertexArray();
  if (!other.vbo_)
    return *this;

  if (!other.ref_count_)
    other.ref_count_ = new int(1);

  vbo_ = other.vbo_;
  vao_ = other.vao_;
  ref_count_ = other.ref_count_;
  size_ = other.size_;

  (*ref_count_)++;
  return *this;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
  std::swap(vbo_, other.vbo_);
  std::swap(vao_, other.vao_);
  std::swap(size_, other.size_);
  std::swap(ref_count_, other.ref_count_);
  return *this;
}

/// Constructor for a vector of 2D vertices.
/// @param array A set of 2D triangles.
VertexArray::VertexArray(const std::vector<Vertex2D>& array) {
  size_ = array.size();
  Allocate(sizeof(Vertex2D), (void*)array.data());
  Vertex2D::Bind();
}

/// Constructor for a vector of 3D vertices.
/// @param array A set of 3D triangles.
VertexArray::VertexArray(const std::vector<Vertex3D>& array) {
  size_ = array.size();
  Allocate(sizeof(Vertex3D), (void*)array.data());
  Vertex3D::Bind();
}

/// @brief The size of the GPU array.
/// @return the number of vertices in the GPU array.
size_t VertexArray::size() const {
  return size_;
}

bool VertexArray::operator==(const smk::VertexArray& other) const {
  return vbo_ == other.vbo_;
}

bool VertexArray::operator!=(const smk::VertexArray& other) const {
  return vbo_ != other.vbo_;
}

void VertexArray::Release() {
  // Nothing to do for the null VertexArray.
  if (!vbo_)
    return;

  // Transfert state to local.
  GLuint vbo = 0;
  GLuint vao = 0;
  int* ref_count = nullptr;
  std::swap(vbo, vbo_);
  std::swap(vao, vao_);
  std::swap(ref_count, ref_count_);

  // Early return without releasing the resource if it is still hold by copy of
  // this class.
  if (ref_count) {
    --(*ref_count);
    if (*ref_count)
      return;
    delete ref_count;
    ref_count = nullptr;
  }

  // Release the OpenGL objects.
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

}  // namespace smk.
