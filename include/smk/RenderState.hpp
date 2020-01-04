// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_RENDER_STATE_HPP
#define SMK_RENDER_STATE_HPP

#include <glm/glm.hpp>
#include <smk/BlendMode.hpp>
#include <smk/Shader.hpp>
#include <smk/Texture.hpp>
#include <smk/VertexArray.hpp>

namespace smk {

struct RenderState {
  ShaderProgram* shader_program = nullptr;
  Texture texture;
  VertexArray vertex_array;
  glm::mat4 view;
  glm::vec4 color;
  BlendMode blend_mode = BlendMode::Alpha;
};

}  // namespace smk

#endif /* end of include guard: SMK_RENDER_STATE_HPP */
