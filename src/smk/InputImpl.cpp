// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <GLFW/glfw3.h>

#include <cmath>
#include <queue>
#include <smk/Input.hpp>
#include <smk/InputImpl.hpp>
#include <vector>

#ifdef __EMSCRIPTEN__
  #include <emscripten.h>
  #include <emscripten/html5.h>

  #include <cmath>
#endif

namespace smk {

void InputImpl::Update(GLFWwindow* window) {
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
    touching_ = true;
  } else if (touching_) {
    touching_ = false;
    cursor_press_ = false;
  } else {
    cursor_ = mouse_;
    cursor_press_ = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
  }

  // Update scroll.
  scroll_old_ = scroll_;
  scroll_ = glm::vec2(0.f, 0.f);
}

#ifdef __EMSCRIPTEN__
void InputImpl::OnTouchEvent(int eventType,
                             const EmscriptenTouchEvent* keyEvent) {
  for (int i = 0; i < keyEvent->numTouches; ++i) {
    const EmscriptenTouchPoint& touch = keyEvent->touches[i];

    if (eventType == EMSCRIPTEN_EVENT_TOUCHSTART ||
        eventType == EMSCRIPTEN_EVENT_TOUCHMOVE) {
      TouchDataPoint data = {
          glm::vec2(touch.targetX, touch.targetY),
          0.f,
      };
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

void InputImpl::OnScrollEvent(glm::vec2 offset) {
  scroll_ += offset;
}

bool InputImpl::IsKeyPressed(int key) {
  auto p = key_state_[key];
  return ((p.first == GLFW_PRESS) && (p.second == GLFW_RELEASE));
}

bool InputImpl::IsKeyReleased(int key) {
  auto p = key_state_[key];
  return ((p.first == GLFW_RELEASE) && (p.second == GLFW_PRESS));
}

bool InputImpl::IsKeyHold(int key) {
  auto p = key_state_[key];
  return (p.first == GLFW_PRESS);
}

bool InputImpl::IsMousePressed(int key) {
  auto p = mouse_state_[key];
  return ((p.first == GLFW_PRESS) && (p.second == GLFW_RELEASE));
}

bool InputImpl::IsMouseReleased(int key) {
  auto p = mouse_state_[key];
  return ((p.first == GLFW_RELEASE) && (p.second == GLFW_PRESS));
}

glm::vec2 InputImpl::mouse() const {
  return mouse_;
}

std::map<Input::FingerID, Touch>& InputImpl::touches() {
  return touches_;
}

bool InputImpl::IsMouseHeld(int key) {
  auto p = mouse_state_[key];
  return (p.first == GLFW_PRESS);
}

bool InputImpl::IsCursorHeld() {
  return cursor_press_ && cursor_press_previous_;
}

bool InputImpl::IsCursorPressed() {
  return cursor_press_ && !cursor_press_previous_;
}

bool InputImpl::IsCursorReleased() {
  return !cursor_press_ && cursor_press_previous_;
}

glm::vec2 InputImpl::cursor() const {
  return cursor_;
}
glm::vec2 InputImpl::scroll_offset() const {
  return scroll_old_;
}

class InputImpl::CharacterListenerImpl
    : public Input::CharacterListenerInterface {
 public:
  CharacterListenerImpl(InputImpl* input) : input_(input) {
    input_->BindCharacterListener(this);
  }
  ~CharacterListenerImpl() override { input_->UnBindCharacterListener(this); }

  bool Receive(wchar_t* c) override {
    if (queue_.empty())
      return false;

    *c = queue_.front();
    queue_.pop();
    return true;
  }

  InputImpl* input_;
  std::queue<wchar_t> queue_;
};

void InputImpl::BindCharacterListener(
    InputImpl::CharacterListenerImpl* listener) {
  character_listeners_.insert(listener);
}

void InputImpl::UnBindCharacterListener(
    InputImpl::CharacterListenerImpl* listener) {
  character_listeners_.erase(listener);
}

void InputImpl::OnCharacterTyped(wchar_t character) {
  for (auto& it : character_listeners_)
    it->queue_.push(character);
}

Input::CharacterListener InputImpl::MakeCharacterListener() {
  return std::make_unique<CharacterListenerImpl>(this);
}

}  // namespace smk
