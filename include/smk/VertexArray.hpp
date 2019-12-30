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

// An array of smk::Vertex moved to the GPU memory.
class VertexArray {
 public:
  VertexArray();  // The invalidVertexArray.

  VertexArray(const std::vector<Vertex2D>& array);
  VertexArray(const std::vector<Vertex3D>& array);

  ~VertexArray();

  void Bind() const;
  void UnBind() const;

  // --- Movable-Copyable resource ---------------------------------------------
  VertexArray(VertexArray&&);
  VertexArray(const VertexArray&);
  VertexArray& operator=(VertexArray&&);
  VertexArray& operator=(const VertexArray&);
  // ---------------------------------------------------------------------------

  int size() const { return size_; }

 private:
  void Allocate(int element_size, void* data);

  GLuint vbo_ = 0;
  GLuint vao_ = 0;
  int size_ = 0;

  // Used to support copy. Nullptr as long as this class is not copied.
  // Otherwise an integer counting how many instances shares this resource.
  mutable int* ref_count_ = nullptr;
};

}  // namespace smk.

#endif /* end of include guard: SMK_VERTEX_ARRAY_HPP */
