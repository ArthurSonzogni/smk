// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VERTEX_ARRAY_HPP
#define SMK_VERTEX_ARRAY_HPP

#include <smk/OpenGL.hpp>
#include <smk/Vertex.hpp>
#include <vector>

namespace smk {

// An array of smk::Vertex moved to the CPU memory.
class VertexArray {
 public:
  VertexArray();  // The invalidVertexArray.
  VertexArray(const std::vector<Vertex>& array);
  ~VertexArray();

  void Bind() const;
  void UnBind() const;

  // --- Move only resource ----------------------------------------------------
  VertexArray(VertexArray&&);
  VertexArray(const VertexArray&) = delete;
  void operator=(VertexArray&&);
  void operator=(const VertexArray&) = delete;
  // ---------------------------------------------------------------------------
  
  int size() const { return size_;} 

 private:
  GLuint vbo_ = 0;
  GLuint vao_ = 0;
  int size_ = 0;
};

}  // namespace smk.

#endif /* end of include guard: SMK_VERTEX_ARRAY_HPP */
