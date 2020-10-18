// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VERTEX_ARRAY_HPP
#define SMK_VERTEX_ARRAY_HPP

#include <initializer_list>
#include <smk/OpenGL.hpp>
#include <smk/Vertex.hpp>
#include <vector>

namespace smk {

/// @brief An array of smk::Vertex moved to the GPU memory. This represent a set
/// of triangles to be drawn by the GPU.
///
/// This class is movable and copyable. It is refcounted. The GPU data is
/// automatically released when the last smk::VertextArray is deleted.
class VertexArray {
 public:
  VertexArray();  // The null VertexArray.
  VertexArray(const std::vector<Vertex2D>& array);
  VertexArray(const std::vector<Vertex3D>& array);

  ~VertexArray();

  void Bind() const;
  void UnBind() const;

  // --- Movable-Copyable resource ---------------------------------------------
  VertexArray(VertexArray&&) noexcept;
  VertexArray(const VertexArray&);
  VertexArray& operator=(VertexArray&&) noexcept;
  VertexArray& operator=(const VertexArray&);
  // ---------------------------------------------------------------------------
  bool operator==(const smk::VertexArray&) const;
  bool operator!=(const smk::VertexArray&) const;

  size_t size() const;

 private:
  void Allocate(int element_size, void* data);
  void Release();

  GLuint vbo_ = 0;
  GLuint vao_ = 0;
  size_t size_ = 0u;

  // Used to support copy. Nullptr as long as this class is not copied.
  // Otherwise an integer counting how many instances shares this resource.
  mutable int* ref_count_ = nullptr;
};

}  // namespace smk.

#endif /* end of include guard: SMK_VERTEX_ARRAY_HPP */
