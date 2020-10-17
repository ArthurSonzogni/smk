// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_WINDOW_HPP
#define SMK_WINDOW_HPP

#include <functional>
#include <glm/glm.hpp>
#include <memory>
#include <smk/RenderTarget.hpp>
#include <string>

struct GLFWwindow;

namespace smk {

class View;
class VertexArray;
class Sprite;
class Input;
class InputImpl;

/// @brief A window. You can draw objects on the window.
///
/// Example:
/// --------
/// ~~~cpp
/// auto window = smk::Window(640, 480, "Window title");
/// ~~~
class Window : public RenderTarget {
 public:
  Window();
  Window(int width, int height, const std::string& title);
  ~Window();

  GLFWwindow* window() const;
  float time() const;
  Input& input();

  void ExecuteMainLoop(std::function<void(void)> loop);
  void ExecuteMainLoopUntil(std::function<bool(void)> loop);

  // Pool new events. This update the |input()| element.
  void PoolEvents();

  // Notify the current frame is ready to be displayed. The current and next one
  // are swapped.
  void Display();

  // Wait until the end of the frame to maintain a targetted frame per seconds.
  // (optional).
  void LimitFrameRate(float fps);

  // Returns true when the user wants to close the window.
  bool ShouldClose();

  // Move-only ressource.
  Window(Window&&) noexcept;
  Window(const Window&) = delete;
  void operator=(Window&&) noexcept;
  void operator=(const Window&) = delete;

 private:
  GLFWwindow* window_ = nullptr;

  // Time:
  float time_ = 0.f;
  float time_last_sleep_ = 0.f;

  void UpdateDimensions();

  std::unique_ptr<InputImpl> input_;
  int id_ = 0;

  std::string module_canvas_selector_;
};

}  // namespace smk

#endif /* end of include guard: SMK_WINDOW_HPP */
