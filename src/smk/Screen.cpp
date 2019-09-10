// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Screen.hpp>

#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include <smk/Color.hpp>
#include <smk/Drawable.hpp>
#include <smk/Input.hpp>
#include <smk/OpenGL.hpp>
#include <smk/View.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <cmath>
#endif

namespace smk {

Screen::Screen() {}
Screen::Screen(int width, int height, const std::string& title)
    : width_(width), height_(height) {

  // initialize the GLFW library
  if (!glfwInit()) {
    throw std::runtime_error("Couldn't init GLFW");
  }

  // setting the opengl version
#ifdef __EMSCRIPTEN__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  // create the window_
  window_ = glfwCreateWindow(width_, height_, title.c_str(), NULL, NULL);
  if (!window_) {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window_");
  }

  glfwMakeContextCurrent(window_);

#ifndef __EMSCRIPTEN__
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error(std::string("Could initialize GLEW, error = ") +
                             (const char*)glewGetErrorString(err));
  }
#endif

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported " << version << std::endl;

  // Alpha transparency.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  View default_view;
  default_view.SetCenter(width_ / 2, height_ / 2);
  default_view.SetSize(width_, height_);
  SetView(default_view);

  vertex_shader = Shader::FromString(R"(
    layout(location = 0) in vec2 space_position;
    layout(location = 1) in vec2 texture_position;

    uniform mat4 view;

    out vec2 f_texture_position;

    void main() {
      f_texture_position = texture_position;
      gl_Position = view * vec4(space_position, 0.0, 1.0);
    }
  )", GL_VERTEX_SHADER);

  fragment_shader = Shader::FromString(R"(
    in vec2 f_texture_position;
    uniform sampler2D tex;
    uniform vec4 color;
    out vec4 out_color;

    void main() {
      out_color = texture(tex, f_texture_position) * color;
    }
  )", GL_FRAGMENT_SHADER);

  program.AddShader(vertex_shader);
  program.AddShader(fragment_shader);
  program.Link();

  program.use();
  program.setUniform("tex", 0);
  program.setUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
  program.setUniform("view", glm::mat4(1.0));
}

Screen::Screen(Screen&& screen) {
  operator=(std::move(screen));
}

void Screen::operator=(Screen&& other) {
  std::swap(fragment_shader, other.fragment_shader);
  std::swap(height_, other.height_);
  std::swap(program, other.program);
  std::swap(time_, other.time_);
  std::swap(time_, other.time_);
  std::swap(vertex_shader, other.vertex_shader);
  std::swap(view_, other.view_);
  std::swap(view_mat_, other.view_mat_);
  std::swap(width_, other.width_);
  std::swap(window_, other.window_);
}

void Screen::PoolEvents() {
  glfwPollEvents();
  input_.Update(window_);
}

void Screen::Display() {
  // Swap Front and Back buffers (double buffering)

  glfwSwapBuffers(window_);

  // Detect window_ related changes
  UpdateDimensions();

  time_ = glfwGetTime();
}

Screen::~Screen() {
  // glfwTerminate(); // Needed? What about multiple windows?
}

void Screen::UpdateDimensions() {
  int width = width_;
  int height = height_;
#ifdef __EMSCRIPTEN__
  emscripten_get_canvas_element_size("canvas", &width_, &height_);
#else
  glfwGetWindowSize(window_, &width_, &height_);
#endif

  if (width != width_ || height != height_) {
    glViewport(0, 0, width_, height_);
    SetView(view_);
  }
}

void Screen::Draw(const Drawable& drawable) {
  RenderState state;
  state.view = view_mat_;
  state.color = smk::Color::White;
  state.vertex_array = nullptr;
  state.texture = nullptr;
  state.blend_mode = smk::BlendMode::Alpha;
  drawable.Draw(*this, state);
}

Texture* WhiteTexture();

void Screen::Draw(const RenderState& state) {
  // Vertex Array
  if (cached_render_state_.vertex_array != state.vertex_array) {
    cached_render_state_.vertex_array = state.vertex_array;
    state.vertex_array->Bind();
  }

  program.use();

  // Color
  if (cached_render_state_.color != state.color) {
    cached_render_state_.color = state.color;
    program.setUniform("color", state.color);
  }

  // View (not cached)
  program.setUniform("view", state.view);

  // Texture
  auto* texture = state.texture;
  if (!texture)
    texture = WhiteTexture();
  if (cached_render_state_.texture != texture) {
    cached_render_state_.texture = texture;
    texture->Bind();
  }

  if (cached_render_state_.blend_mode != state.blend_mode) {
    cached_render_state_.blend_mode = state.blend_mode;
    glEnable(GL_BLEND);
    glBlendEquationSeparate(state.blend_mode.equation_rgb,
                            state.blend_mode.equation_alpha);
    glBlendFuncSeparate(state.blend_mode.src_rgb, state.blend_mode.dst_rgb,
                        state.blend_mode.src_alpha, state.blend_mode.dst_alpha);
  }

  glDrawArrays(GL_TRIANGLES, 0, state.vertex_array->size());
}

void Screen::SetView(const View& view) {
  view_ = view;
  float z_x = +2.0 / view.width_;   // [0, width]  -> [-1,1]
  float z_y = -2.0 / view.height_;  // [0, height] -> [-1,1]
  float t_x = -view.x_ * z_x;
  float t_y = -view.y_ * z_y;
  view_mat_ = glm::mat4(z_x, 0.0, 0.0, 0.0,   //
                        0.0, z_y, 0.0, 0.0,   //
                        0.0, 0.0, 1.0, 0.0,   //
                        t_x, t_y, 0.0, 1.0);  //
}

void Screen::Clear(const glm::vec4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::LimitFrameRate(float fps) {
  const float delta = glfwGetTime() - time_last_sleep_;
  const float target = 1.f / fps;
  float sleep_duration = target - delta;
  sleep_duration = std::max(0.f, std::min(target, sleep_duration));
  std::this_thread::sleep_for(
      std::chrono::microseconds(int(sleep_duration * 1'000'000)));
  time_last_sleep_ = glfwGetTime();
}

static Texture white_texture;
Texture* WhiteTexture() {
  if (white_texture.id == 0) {
    white_texture.width = 1;
    white_texture.height = 1;
    const uint8_t data[4] = {255, 255, 255, 255};
    glGenTextures(1, &white_texture.id);
    glBindTexture(GL_TEXTURE_2D, white_texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, white_texture.width,
                 white_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
  }
  return &white_texture;
}


} // namespace smk
