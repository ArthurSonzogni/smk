// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VERTEX_HPP
#define SMK_VERTEX_HPP

#include <glm/glm.hpp>

namespace smk {

struct Vertex {
  glm::vec2 space_position;
  glm::vec2 texture_position;
};

} // namespace smk.

#endif /* end of include guard: SMK_VERTEX_HPP */
