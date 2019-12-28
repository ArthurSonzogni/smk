#include <iostream>
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
#include <cmath>
#endif

namespace smk {

void Input::Update(GLFWwindow* window) {
  // Get window dimension.
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

  cursor_press_previous_ = cursor_press_;
  if (TouchCount()) {
    cursor_ = GetTouch(0)->position;
    cursor_press_ = true;
  } else {
    cursor_ = mouse_;
    cursor_press_ = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
  }
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

#ifdef __EMSCRIPTEN__
void Input::OnTouchEvent(int eventType, const EmscriptenTouchEvent* keyEvent) {
  for(int i = 0; i<keyEvent->numTouches; ++i) {
    const EmscriptenTouchPoint& touch = keyEvent->touches[i];

    if (eventType == EMSCRIPTEN_EVENT_TOUCHSTART) {
      touch_[touch.identifier] = Touch{
          glm::vec2(touch.targetX, touch.targetY),
          touch.identifier,
      };
      touch_ids_.push_back(touch.identifier);
      return;
    }

    if (eventType == EMSCRIPTEN_EVENT_TOUCHMOVE) {
      touch_[touch.identifier] = Touch{
          glm::vec2(touch.targetX, touch.targetY),
          touch.identifier,
      };
      return;
    }

    auto it =
        std::find(touch_ids_.begin(), touch_ids_.end(), touch.identifier);
    touch_ids_.erase(it);
  }
}
#endif

int Input::TouchCount() {
  return touch_ids_.size();
}

Input::Touch* Input::GetTouch(int index) {
  return GetTouchById(touch_ids_[index]);
}

Input::Touch* Input::GetTouchById(int id) {
  auto it = touch_.find(id);
  if (it == touch_.end())
    return nullptr;
  return &(it->second);
}

bool Input::IsCursorHold() {
  return cursor_press_ && cursor_press_previous_;
}

bool Input::IsCursorPressed() {
  return cursor_press_ && !cursor_press_previous_;
}

bool Input::IsCursorReleased() {
  return !cursor_press_ && cursor_press_previous_;
}

glm::vec2 Input::cursor() {
  return cursor_;
}

}  // namespace smk
