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

/// Contain all the data needed to draw 
struct RenderState {
  ShaderProgram* shader_program = nullptr;  ///< The shader used.
  Texture texture;                          ///< The texture 0 bound.
  VertexArray vertex_array;                 ///< The shape to to be drawn
  glm::mat4 view;                           ///< The "view" transformation.
  glm::vec4 color;                          ///< The masking color.
  BlendMode blend_mode = BlendMode::Alpha;  ///< The OpenGL BlendMode
};

}  // namespace smk

#endif /* end of include guard: SMK_RENDER_STATE_HPP */
