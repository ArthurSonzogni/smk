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

/// Called by smk::Window. This update the keyboard and mouse state.
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

  // Update cursor.
  cursor_press_previous_ = cursor_press_;
  if (touches_.size()) {
    cursor_ = touches_.begin()->second.position();
    cursor_press_ = true;
  } else {
    cursor_ = mouse_;
    cursor_press_ = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
  }
}

/// @brief Whether a keyboard button is pressed or not.
/// @return true whenever a keyboard button is pressed.
/// @param key The keyboard button.
bool Input::IsKeyPressed(int key) {
  auto p = key_state_[key];
  return ((p.first == GLFW_PRESS) && (p.second == GLFW_RELEASE));
}

/// @brief Whether a keyboard button is released or not.
/// @return true whenever a keyboard button is released
/// @param key The keyboard button.
bool Input::IsKeyReleased(int key) {
  auto p = key_state_[key];
  return ((p.first == GLFW_RELEASE) && (p.second == GLFW_PRESS));
}

/// @brief Whether a keyboard button is down or not.
/// @return true whenever a keyboard button is hold.
/// @param key The keyboard button.
bool Input::IsKeyHold(int key) {
  auto p = key_state_[key];
  return (p.first == GLFW_PRESS);
}

/// @brief Whether a mouse button is pressed or not.
/// @return true whenever a mouse button is pressed.
/// @param key The mouse button.
bool Input::IsMousePressed(int key) {
  auto p = mouse_state_[key];
  return ((p.first == GLFW_PRESS) && (p.second == GLFW_RELEASE));
}

/// @brief Whether a mouse button is released or not.
/// @return true whenever a mouse button is released
/// @param key The mouse button.
bool Input::IsMouseReleased(int key) {
  auto p = mouse_state_[key];
  return ((p.first == GLFW_RELEASE) && (p.second == GLFW_PRESS));
}

/// @brief The mouse position.
/// @return the mouse position.
glm::vec2 Input::mouse() {
  return mouse_;
}

/// @brief The touch states.
/// @return the touches states.
std::map<Input::FingerID, Touch>& Input::touches() {
  return touches_;
}

/// @brief Whether a mouse button is down or not.
/// @return true whenever a mouse button is hold.
/// @param key The mouse button.
bool Input::IsMouseHold(int key) {
  auto p = mouse_state_[key];
  return (p.first == GLFW_PRESS);
}

#ifdef __EMSCRIPTEN__
void Input::OnTouchEvent(int eventType, const EmscriptenTouchEvent* keyEvent) {
  for (int i = 0; i < keyEvent->numTouches; ++i) {
    const EmscriptenTouchPoint& touch = keyEvent->touches[i];

    if (eventType == EMSCRIPTEN_EVENT_TOUCHSTART ||
        eventType == EMSCRIPTEN_EVENT_TOUCHMOVE) {
      auto data = TouchDataPoint{glm::vec2(touch.targetX, touch.targetY), 0.f};
      auto& internal_touch = touches_[touch.identifier];
      internal_touch.finger_id = touch.identifier;
      internal_touch.data_points.push_back(data);
      continue;
    }

    auto it = touches_.find(touch.identifier);
    if (it != touches_.end())
      touches_.erase(it);
  }
}
#endif


/// @brief Whether the cursor is down or not.
/// @return true whenever the cursor is down.
bool Input::IsCursorHold() {
  return cursor_press_ && cursor_press_previous_;
}

/// @brief Whether the cursor is pressed or not
/// @return true whenever the cursor is pressed.
bool Input::IsCursorPressed() {
  return cursor_press_ && !cursor_press_previous_;
}

/// @brief Whether the cursor is released or not
/// @return true whenever the cursor is released.
bool Input::IsCursorReleased() {
  return !cursor_press_ && cursor_press_previous_;
}

/// @brief The cursor position.
/// @return the cursor position.
glm::vec2 Input::cursor() {
  return cursor_;
}

}  // namespace smk
