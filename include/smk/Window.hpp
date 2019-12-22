// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_WINDOW_HPP
#define SMK_WINDOW_HPP

#include <functional>
#include <string>

#include <glm/glm.hpp>

#include <memory>
#include <smk/Input.hpp>
#include <smk/RenderTarget.hpp>

struct GLFWwindow;

namespace smk {

class View;
class VertexArray;
class Sprite;

// Represent a window.
class Window : public RenderTarget {
 public:
  Window();
  Window(int width, int height, const std::string& title);
  Window(Window&&);
  Window(const Window&) = delete;
  void operator=(Window&&);
  void operator=(const Window&) = delete;
  ~Window();

  // Various data about the current window.
  // Nothing
  GLFWwindow* window() const { return window_; }

  // The time of the current frame
  float time() const { return time_; }

  Input& input() { return input_; }

  // Pool new events. This update the |input()| element.
  void PoolEvents();

  // Notify the current frame is ready to be displayed. The current and next one
  // are swapped.
  void Display();

  // Wait until the end of the frame to maintain a targetted frame per
  // seconds. (optional).
  void LimitFrameRate(float fps);

 private:
  GLFWwindow* window_ = nullptr;

  // Time:
  float time_ = 0.f;
  float time_last_sleep_ = 0.f;

  void UpdateDimensions();

  Input input_;
};

}  // namespace smk

#endif /* end of include guard: SMK_WINDOW_HPP */
