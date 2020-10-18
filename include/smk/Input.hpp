// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_INPUT_HPP
#define SMK_INPUT_HPP

#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <smk/Touch.hpp>
#include <vector>

struct GLFWwindow;
struct EmscriptenTouchEvent;

namespace smk {

/// @brief A class for querying input state (keyboard, mouse, touch).
/// The Input class is tied to a smk::Window. You need to call regularly
/// smk::Screen::PoolEvent to update the input state.
///
/// To know keyboard and mouse buttons identifer, you need to refer to the GLFW
/// definitions:
/// * [keyboard buttons](https://www.glfw.org/docs/latest/group__keys.html)
/// * [mouse buttons](https://www.glfw.org/docs/latest/group__buttons.html)
///
/// @see smk::Window::PoolEvents()
class Input {
 public:
  virtual ~Input() {}
  // Keyboard ------------------------------------------------------------------

  /// @brief Whether a keyboard button is down or not.
  /// @return true whenever a keyboard button is hold.
  /// @param key The keyboard button.
  virtual bool IsKeyHold(int key) = 0;
  /// @brief Whether a keyboard button is pressed or not.
  /// @return true whenever a keyboard button is pressed.
  /// @param key The keyboard button.
  virtual bool IsKeyPressed(int key) = 0;
  /// @brief Whether a keyboard button is released or not.
  /// @return true whenever a keyboard button is released
  /// @param key The keyboard button.
  virtual bool IsKeyReleased(int key) = 0;

  // Mouse ---------------------------------------------------------------------

  /// @brief Whether a mouse button is down or not.
  /// @return true whenever a mouse button is hold.
  /// @param key The mouse button.
  virtual bool IsMouseHeld(int key) = 0;
  /// @brief Whether a mouse button is pressed or not.
  /// @return true whenever a mouse button is pressed.
  /// @param key The mouse button.
  virtual bool IsMousePressed(int key) = 0;
  /// @brief Whether a mouse button is released or not.
  /// @return true whenever a mouse button is released
  /// @param key The mouse button.
  virtual bool IsMouseReleased(int key) = 0;
  /// @brief The mouse position.
  /// @return the mouse position.
  virtual glm::vec2 mouse() const = 0;

  // Touch.
  using FingerID = int;

  /// @brief The touch states.
  /// @return the touches states.
  virtual std::map<FingerID, Touch>& touches() = 0;

  // Cursor --------------------------------------------------------------------
  // A cursor is either the mouse or a touch. This is choosen smartly.

  /// @brief Whether the cursor is down or not.
  /// @return true whenever the cursor is down.
  virtual bool IsCursorHeld() = 0;
  /// @brief Whether the cursor is pressed or not
  /// @return true whenever the cursor is pressed.
  virtual bool IsCursorPressed() = 0;
  /// @brief Whether the cursor is released or not
  /// @return true whenever the cursor is released.
  virtual bool IsCursorReleased() = 0;
  /// @brief The cursor position.
  /// @return the cursor position.
  virtual glm::vec2 cursor() const = 0;

  // Scroll -------------------------------------------------------------------

  /// @brief The mouse/touchpad scrolling offset since the last frame.
  /// @return the scrolling offset.
  virtual glm::vec2 scroll_offset() const = 0;

  // Character listener --------------------------------------------------------
  //
  /// @brief Receive characters typed from the keyboard.
  /// All the keyboard modifiers are applied (Shift, Ctrl, Alt, ...). Useful for
  /// implementing input boxes.
  ///
  /// Usage:
  /// -----
  /// ~~~cpp
  /// // Initialization
  /// auto listener = input.MakeCharacterListener();
  /// ~~~
  ///
  /// ~~~cpp
  /// // Main loop.
  /// wchar_t character;
  /// while(listener->Receive(&character))
  ///   character_typed += character;
  /// ~~~
  class CharacterListenerInterface {
   public:
    virtual bool Receive(wchar_t* in) = 0;
    virtual ~CharacterListenerInterface() = default;
  };
  using CharacterListener = std::unique_ptr<CharacterListenerInterface>;
  virtual CharacterListener MakeCharacterListener() = 0;
};

}  // namespace smk

#endif /* end of include guard: SMK_INPUT_HPP */
