// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_RENDER_TARGET_HPP
#define SMK_RENDER_TARGET_HPP

#include <glm/glm.hpp>
#include <memory>
#include <smk/RenderState.hpp>
#include <smk/Shader.hpp>
#include <smk/VertexArray.hpp>
#include <smk/View.hpp>

namespace smk {

class Drawable;
struct RenderState;

/// A texture where things can be / a smk::Drawable can be drawn on.
///
/// Implementated by:
///  * Window
///  * Framebuffer.
class RenderTarget {
 public:
  RenderTarget();
  RenderTarget(RenderTarget&&);
  RenderTarget(const RenderTarget&) = delete;
  void operator=(RenderTarget&&);
  void operator=(const RenderTarget& other) = delete;

  // 0. Clear the framebuffer
  void Clear(const glm::vec4& color);

  // 1. Set the view
  void SetView(const View& view);
  void SetView(const glm::mat4& mat);
  const View& GetView() const;

  // 2. Set a shader to render elements.
  void SetShaderProgram(ShaderProgram* shader_program);
  ShaderProgram* shader_program_2d();
  ShaderProgram* shader_program_3d();

  // 3. Draw some stuff.
  virtual void Draw(const Drawable&);
  virtual void Draw(const RenderState&);

  // Surface dimensions:
  glm::vec2 dimension() const;
  int width() const;
  int height() const;

  // Bind the OpenGL RenderFrame. This function is useless, because it is called
  // automatically for you. Use this only when you use direct OpenGL call.
  static void Bind(RenderTarget*);

 protected:
  void InitRenderTarget();

  int width_ = 0;
  int height_ = 0;

  // View:
  glm::mat4 projection_matrix_;
  smk::View view_;

  // Shaders:
  Shader vertex_shader_2d_;
  Shader fragment_shader_2d_;
  std::unique_ptr<ShaderProgram> shader_program_2d_;

  Shader vertex_shader_3d_;
  Shader fragment_shader_3d_;
  std::unique_ptr<ShaderProgram> shader_program_3d_;

  // Current shader program.
  ShaderProgram* shader_program_;

  GLuint frame_buffer_ = 0;
};

}  // namespace smk

#endif /* end of include guard: SMK_RENDER_TARGET_HPP */
