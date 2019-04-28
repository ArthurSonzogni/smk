// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Input.hpp>

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

namespace smk {

void Input::Update(GLFWwindow* window) {
  // get screen dimension
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // Update key
  for (auto it = key_state_.begin(); it != key_state_.end(); ++it) {
    it->second.second = it->second.first;
    it->second.first = glfwGetKey(window, it->first);
  }

  // Update mouse
  for (auto it = mouse_state_.begin(); it != mouse_state_.end(); ++it) {
    it->second.second = it->second.first;
    it->second.first = glfwGetMouseButton(window, it->first);
  }

  // get mouse position
  double mouse_x, mouse_y;
  glfwGetCursorPos(window, &mouse_x, &mouse_y);
  mouse_ = glm::vec2(mouse_x, mouse_y);
}

bool Input::IsKeyPressed(int key) {
  auto p = key_state_[key];
  return ((p.first == GLFW_PRESS) && (p.second == GLFW_RELEASE));
}

bool Input::IsKeyReleased(int key) {
  auto p = key_state_[key];
  return ((p.first == GLFW_RELEASE) && (p.second == GLFW_PRESS));
}

bool Input::IsKeyHold(int key) {
  auto p = key_state_[key];
  return (p.first == GLFW_PRESS);
}

bool Input::IsMousePressed(int key) {
  auto p = mouse_state_[key];
  return ((p.first == GLFW_PRESS) && (p.second == GLFW_RELEASE));
}

bool Input::IsMouseReleased(int key) {
  auto p = mouse_state_[key];
  return ((p.first == GLFW_RELEASE) && (p.second == GLFW_PRESS));
}

bool Input::IsMouseHold(int key) {
  auto p = mouse_state_[key];
  return (p.first == GLFW_PRESS);
}

}  // namespace smk
