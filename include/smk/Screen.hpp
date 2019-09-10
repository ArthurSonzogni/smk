// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SCREEN_HPP
#define SMK_SCREEN_HPP

#include <functional>
#include <string>

#include <glm/glm.hpp>

#include <smk/Input.hpp>
#include <smk/RenderState.hpp>
#include <smk/Shader.hpp>
#include <smk/VertexArray.hpp>
#include <smk/View.hpp>

struct GLFWwindow;

namespace smk {

class Drawable;
class View;
class VertexArray;
class Sprite;

class Screen {
 public:
  Screen();
  Screen(int width, int height, const std::string& title);

  ~Screen();

  // Various data about the current window.
  int height() const { return height_; }
  int width() const { return width_; }
  glm::vec2 dimension() const { return glm::vec2(width_, height_); }
  float time() const { return time_; }
  GLFWwindow* window() const { return window_; }
  Input& input() { return input_; }

  // 0. Pool events. This updates the Input object.
  void PoolEvents();

  // 1. Clear the previous frame
  void Clear(const glm::vec4& color);

  // 2. Set the base view transformation.
  void SetView(const View& view);
  const View& GetView() const { return view_; }

  // 3. Draw.
  void Draw(const Drawable&);
  void Draw(const RenderState&);

  // 4. Notify the current frame is ready. The current and next one are swapped.
  void Display();

  // 5. Wait until the end of the frame to maintain a targetted frame per
  // seconds. (optional).
  void LimitFrameRate(float fps);

 private:
  GLFWwindow* window_ = nullptr;

  // Time:
  float time_ = 0.f;
  float time_last_sleep_ = 0.f;

  // Dimensions:
  int width_ = 0;
  int height_ = 0;

  // View:
  glm::mat4 view_mat_;
  smk::View view_;

  void UpdateDimensions();
  // -------- Movable only class.-----------------------------------------------
 public:
  Screen(Screen&&);          // Movable object
  void operator=(Screen&&);  // Movable object.
 private:
  Screen(const Screen&) = delete;          // Non copyable object.
  void operator=(const Screen&) = delete;  // Non copyable object.

  friend Sprite;

  Shader vertex_shader;
  Shader fragment_shader;
  ShaderProgram program;

  Input input_;

  RenderState cached_render_state_;
};

}  // namespace smk

#endif /* end of include guard: SMK_SCREEN_HPP */
