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
  const View& GetView() const { return view_; }

  // 2. Set a shader to render elements.
  void SetShaderProgram(ShaderProgram* shader_program);
  ShaderProgram* shader_program_2d() { return shader_program_2d_.get(); };
  ShaderProgram* shader_program_3d() { return shader_program_3d_.get(); };

  // 3. Draw some stuff.
  virtual void Draw(const Drawable&);
  virtual void Draw(const RenderState&);

  int height() const { return height_; }
  int width() const { return width_; }
  glm::vec2 dimension() const { return glm::vec2(width_, height_); }

 protected:
  void InitRenderTarget();

  static void Bind(RenderTarget*);

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
