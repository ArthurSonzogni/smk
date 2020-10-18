// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Color.hpp>
#include <smk/Drawable.hpp>
#include <smk/RenderTarget.hpp>
#include <smk/Texture.hpp>

namespace smk {
bool g_invalidate_textures = false;
namespace {

const Texture& WhiteTexture() {
  static const smk::Texture white_texture = [] {
    static const uint8_t data[4] = {255, 255, 255, 255};
    return smk::Texture(data, 1, 1);
  }();

  return white_texture;
}

RenderTarget* render_target = nullptr;
RenderState cached_render_state_;

}  // namespace

void RenderTarget::Bind(RenderTarget* target) {
  if (render_target == target)
    return;
  render_target = target;
  glBindFramebuffer(GL_FRAMEBUFFER, render_target->frame_buffer_);
  glViewport(0, 0, render_target->width_, render_target->height_);
}

/// @brief Build an invalid RenderTarget.
/// It can be replaced later by using the move operator.
RenderTarget::RenderTarget() {}

/// @brief Constructor from temporary.
RenderTarget::RenderTarget(RenderTarget&& other) noexcept {
  operator=(std::move(other));
}

/// @brief Move operator.
void RenderTarget::operator=(RenderTarget&& other) noexcept {
  std::swap(width_, other.width_);
  std::swap(height_, other.height_);
  std::swap(projection_matrix_, other.projection_matrix_);
  std::swap(view_, other.view_);
  std::swap(vertex_shader_2d_, other.vertex_shader_2d_);
  std::swap(fragment_shader_2d_, other.fragment_shader_2d_);
  std::swap(shader_program_2d_, other.shader_program_2d_);
  std::swap(vertex_shader_3d_, other.vertex_shader_3d_);
  std::swap(fragment_shader_3d_, other.fragment_shader_3d_);
  std::swap(shader_program_3d_, other.shader_program_3d_);
  std::swap(shader_program_, other.shader_program_);
  std::swap(frame_buffer_, other.frame_buffer_);
}

/// @brief Clear the surface with a single color.
/// @param color: An opaque color to fill the surface.
void RenderTarget::Clear(const glm::vec4& color) {
  Bind(this);
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}

/// @brief Set the View to use.
/// @param view: The view to use.
void RenderTarget::SetView(const View& view) {
  view_ = view;
  float z_x = +2.0 / view.width_;   // [0, width]  -> [-1,1]
  float z_y = -2.0 / view.height_;  // [0, height] -> [-1,1]
  float t_x = -view.x_ * z_x;
  float t_y = -view.y_ * z_y;
  SetView(glm::mat4(z_x, 0.0, 0.0, 0.0,    //
                    0.0, z_y, 0.0, 0.0,    //
                    0.0, 0.0, 1.0, 0.0,    //
                    t_x, t_y, 0.0, 1.0));  //
}

/// @brief Set the View to use.
/// @param mat: The matrix to transform from/to the OpenGL space [-1,1]^3 to the
///             screen space.
void RenderTarget::SetView(const glm::mat4& mat) {
  projection_matrix_ = mat;
}

/// @brief Return the View currently assigned to this RenderTarget.
const View& RenderTarget::view() const {
  return view_;
}

/// @brief Set the ShaderProgram to be used.
/// @param shader_program: The ShaderProgram to be used.
///
/// ## Example:
///
/// ~~~cpp
/// auto shader_vertex = Shader::FromString(R"(
///   layout(location = 0) in vec2 space_position;
///   layout(location = 1) in vec2 texture_position;
///
///   uniform mat4 projection;
///   uniform mat4 view;
///
///   out vec2 f_texture_position;
///
///   void main() {
///     f_texture_position = texture_position;
///     gl_Position = projection * view * vec4(space_position, 0.0, 1.0);
///   }
/// )", GL_VERTEX_SHADER);
///
/// fragment_shader_2d_ = Shader::FromString(R"(
///   in vec2 f_texture_position;
///   uniform sampler2D texture_0;
///   uniform vec4 color;
///   out vec4 out_color;
///
///   void main() {
///     vec4 inverted_color = vec4(1.0) - color;
///     out_color = texture(texture_0, f_texture_position) * inverted_color.
///   }
/// )";
///
/// auto shader_program = smk::ShaderProgram>();
/// shader_program.AddShader(vertex_shader_2d_);
/// shader_program.AddShader(fragment_shader_2d_);
/// shader_program.Link();
///
/// window.SetShaderProgram(shader_program);
/// ~~~
/// {
void RenderTarget::SetShaderProgram(ShaderProgram& shader_program) {
  shader_program_ = shader_program;
  shader_program_.Use();
  shader_program_.SetUniform("texture_0", 0);
  shader_program_.SetUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
  shader_program_.SetUniform("projection", glm::mat4(1.0));
  shader_program_.SetUniform("view", glm::mat4(1.0));
}

/// @brief Return the default predefined 2D shader program. It is bound by
/// default.
ShaderProgram& RenderTarget::shader_program_2d() {
  return shader_program_2d_;
};

/// @brief Return the default predefined 3D shader program.
ShaderProgram& RenderTarget::shader_program_3d() {
  return shader_program_3d_;
};

/// @brief Draw on the surface
/// @param drawable: The object to be drawn on the surface.
void RenderTarget::Draw(const Drawable& drawable) {
  Bind(this);
  RenderState state;
  state.shader_program = shader_program_;
  state.view = glm::mat4(1.0);
  state.color = smk::Color::White;
  state.blend_mode = smk::BlendMode::Alpha;
  drawable.Draw(*this, state);
}

/// @brief Draw on the surface
/// @param state: The RenderState to be usd for drawing.
void RenderTarget::Draw(RenderState& state) {
  // Vertex Array
  if (cached_render_state_.vertex_array != state.vertex_array) {
    cached_render_state_.vertex_array = state.vertex_array;
    state.vertex_array.Bind();
  }

  // Shader
  if (cached_render_state_.shader_program != state.shader_program) {
    cached_render_state_.shader_program = state.shader_program;
    cached_render_state_.shader_program.Use();
  }

  // Color
  if (cached_render_state_.color != state.color) {
    cached_render_state_.color = state.color;
    cached_render_state_.shader_program.SetUniform("color", state.color);
  }

  // View (not cached)
  state.shader_program.SetUniform("projection", projection_matrix_);
  state.shader_program.SetUniform("view", state.view);

  // Texture
  auto& texture = state.texture.id() ? state.texture : WhiteTexture();
  if (cached_render_state_.texture != texture || g_invalidate_textures) {
    cached_render_state_.texture = texture;
    texture.Bind();
    g_invalidate_textures = false;
  }

  if (cached_render_state_.blend_mode != state.blend_mode) {
    cached_render_state_.blend_mode = state.blend_mode;
    glEnable(GL_BLEND);
    glBlendEquationSeparate(state.blend_mode.equation_rgb,
                            state.blend_mode.equation_alpha);
    glBlendFuncSeparate(state.blend_mode.src_rgb, state.blend_mode.dst_rgb,
                        state.blend_mode.src_alpha, state.blend_mode.dst_alpha);
  }

  glDrawArrays(GL_TRIANGLES, 0, state.vertex_array.size());
}

/// @brief the dimension (width, height) of the drawing area.
/// @return the dimensions in (pixels, pixels) of the surface.
glm::vec2 RenderTarget::dimensions() const {
  return glm::vec2(width_, height_);
}

/// @brief the width of the surface.
/// @return the height of the surface.
int RenderTarget::width() const {
  return width_;
}

/// @brief the height of the surface.
/// @return the height in pixels of the surface.
int RenderTarget::height() const {
  return height_;
}

void RenderTarget::InitRenderTarget() {
  View default_view;
  default_view.SetCenter(width_ / 2, height_ / 2);
  default_view.SetSize(width_, height_);
  SetView(default_view);

  vertex_shader_2d_ = Shader::FromString(R"(
    layout(location = 0) in vec2 space_position;
    layout(location = 1) in vec2 texture_position;

    uniform mat4 projection;
    uniform mat4 view;

    out vec2 f_texture_position;

    void main() {
      f_texture_position = texture_position;
      gl_Position = projection * view * vec4(space_position, 0.0, 1.0);
    }
  )",
                                         GL_VERTEX_SHADER);

  fragment_shader_2d_ = Shader::FromString(R"(
    in vec2 f_texture_position;
    uniform sampler2D texture_0;
    uniform vec4 color;
    out vec4 out_color;

    void main() {
      out_color = texture(texture_0, f_texture_position) * color;
    }
  )",
                                           GL_FRAGMENT_SHADER);

  shader_program_2d_.AddShader(vertex_shader_2d_);
  shader_program_2d_.AddShader(fragment_shader_2d_);
  shader_program_2d_.Link();

  vertex_shader_3d_ = Shader::FromString(R"(
    layout(location = 0) in vec3 space_position;
    layout(location = 1) in vec3 normal;
    layout(location = 2) in vec2 texture_position;

    uniform mat4 projection;
    uniform mat4 view;

    out vec4 fPosition;
    out vec2 fTexture;
    out vec3 fNormal;

    void main() {
      fTexture = texture_position;
      fPosition = view * vec4(space_position,1.0);
      fNormal = vec3(view * vec4(normal,0.0));

      gl_Position = projection * fPosition;
    }
  )",
                                         GL_VERTEX_SHADER);

  fragment_shader_3d_ = Shader::FromString(R"(
    uniform sampler2D texture_0;
    uniform vec4 color;

    uniform vec4 light_position;
    uniform float ambient;
    uniform float diffuse;
    uniform float specular;
    uniform float specular_power;

    in vec4 fPosition;
    in vec2 fTexture;
    in vec3 fNormal;

    out vec4 out_color;

    void main(void)
    {
      vec3 object_dir =-normalize(fPosition.xyz);
      vec3 normal_dir = normalize(fNormal);
      vec3 light_dir = normalize(light_position.xyz-fPosition.xyz);
      vec3 reflect_dir = -reflect(object_dir,normal_dir);

      float diffuse_strength = max(0.0, dot(normal_dir, light_dir));
      float specular_strength = pow(max(0.0, dot(reflect_dir, light_dir)),
                                    specular_power);

      out_color = texture(texture_0, fTexture);
      out_color.rgb *= ambient +
                       diffuse * diffuse_strength +
                       specular * specular_strength;
      out_color *= color;
    }
  )",
                                           GL_FRAGMENT_SHADER);

  shader_program_3d_.AddShader(vertex_shader_3d_);
  shader_program_3d_.AddShader(fragment_shader_3d_);
  shader_program_3d_.Link();

  shader_program_3d_.Use();
  shader_program_3d_.SetUniform("light_position",
                                 glm::vec4(0.f, 5.f, 0.f, 1.f));
  shader_program_3d_.SetUniform("ambient", 0.3f);
  shader_program_3d_.SetUniform("diffuse", 0.5f);
  shader_program_3d_.SetUniform("specular", 0.5f);
  shader_program_3d_.SetUniform("specular_power", 4.0f);

  SetShaderProgram(shader_program_2d_);
}

}  // namespace smk
