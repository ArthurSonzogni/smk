// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#ifndef SMK_INPUTIMPL_H_
#define SMK_INPUTIMPL_H_

#include <smk/Input.hpp>
#include <unordered_set>
#include <vector>

#ifdef __EMSCRIPTEN__
  #include <emscripten.h>
#endif

namespace smk {

class InputImpl : public Input {
 public:
  void Update(GLFWwindow* window);
#ifdef __EMSCRIPTEN__
  void OnTouchEvent(int eventType, const EmscriptenTouchEvent* keyEvent);
#endif
  void OnScrollEvent(glm::vec2 offset);
  void OnCharacterTyped(wchar_t character);

  class CharacterListenerImpl;
  void BindCharacterListener(CharacterListenerImpl*);
  void UnBindCharacterListener(CharacterListenerImpl*);

  // Input override:
  bool IsKeyPressed(int key) override;
  bool IsKeyReleased(int key) override;
  bool IsKeyHold(int key) override;
  bool IsMousePressed(int key) override;
  bool IsMouseReleased(int key) override;
  glm::vec2 mouse() const override;
  std::map<FingerID, Touch>& touches() override;
  bool IsMouseHeld(int key) override;
  bool IsCursorHeld() override;
  bool IsCursorPressed() override;
  bool IsCursorReleased() override;
  glm::vec2 cursor() const override;
  glm::vec2 scroll_offset() const override;
  CharacterListener MakeCharacterListener() override;

 private:
  // Keyboard.
  std::map<int, std::pair<int, int>> key_state_;

  // Mouse.
  std::map<int, std::pair<int, int>> mouse_state_;
  glm::vec2 mouse_ = {0.f, 0.f};

  // Touch.
  std::map<FingerID, Touch> touches_;

  // Cursor
  glm::vec2 cursor_ = {0, 0};
  bool cursor_press_ = false;
  bool cursor_press_previous_ = false;
  bool touching_ = true;

  // Scroll
  glm::vec2 scroll_ = {0.f, 0.f};
  glm::vec2 scroll_old_ = {0.f, 0.f};

  // CharacterListener
  std::unordered_set<CharacterListenerImpl*> character_listeners_;
};

}  // namespace smk
#endif /* end of include guard: SMK_INPUTIMPL_H_ */
