// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_INPUT_HPP
#define SMK_INPUT_HPP

#include <map>
#include <glm/glm.hpp>

struct GLFWwindow;

namespace smk {

class Input {
 public:
  // update state
  void Update(GLFWwindow* window);

  // keyboard
  bool IsKeyHold(int key);
  bool IsKeyPressed(int key);
  bool IsKeyReleased(int key);

  // mouse
  bool IsMouseHold(int key);
  bool IsMousePressed(int key);
  bool IsMouseReleased(int key);
  glm::vec2 mouse() { return mouse_; }

 private:
  std::map<int, std::pair<int, int>> key_state_;
  std::map<int, std::pair<int, int>> mouse_state_;
  glm::vec2 mouse_;
};

}  // namespace smk

#endif /* end of include guard: SMK_INPUT_HPP */
