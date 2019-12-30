// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_INPUT_HPP
#define SMK_INPUT_HPP

#include <glm/glm.hpp>
#include <map>
#include <smk/Touch.hpp>
#include <vector>

struct GLFWwindow;
struct EmscriptenTouchEvent;

namespace smk {

class Input {
 public:
  // Update state.
  void Update(GLFWwindow* window);
#ifdef __EMSCRIPTEN__
  void OnTouchEvent(int eventType, const EmscriptenTouchEvent* keyEvent);
#endif

  // Keyboard.
  bool IsKeyHold(int key);
  bool IsKeyPressed(int key);
  bool IsKeyReleased(int key);

  // Mouse.
  bool IsMouseHold(int key);
  bool IsMousePressed(int key);
  bool IsMouseReleased(int key);
  glm::vec2 mouse() { return mouse_; }

  // Touch.
  using FingerID = int;
  const std::map<FingerID, Touch>& touches() { return touches_; }

  // A cursor is either the mouse or a touch. This is choosen smartly.
  bool IsCursorHold();
  bool IsCursorPressed();
  bool IsCursorReleased();
  glm::vec2 cursor();

 private:
  // Keyboard.
  std::map<int, std::pair<int, int>> key_state_;

  // Mouse.
  std::map<int, std::pair<int, int>> mouse_state_;
  glm::vec2 mouse_;

  // Touch.
  std::map<FingerID, Touch> touches_;

  // Cursor
  glm::vec2 cursor_;
  bool cursor_press_ = false;
  bool cursor_press_previous_ = false;
};

}  // namespace smk

#endif /* end of include guard: SMK_INPUT_HPP */
