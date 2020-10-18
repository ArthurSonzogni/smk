// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_TEXT_HPP
#define SMK_TEXT_HPP

#include <smk/Texture.hpp>
#include <smk/Transformable.hpp>
#include <string>

namespace smk {
class Font;

/// @example text.cpp

/// @brief A class for displaying text.
///
/// A Text uses the Font's glyphs and displays them to the screen. A Text is a
/// Transformable object, so you can  move/rotate/scale/colorize it.
///
/// Example:
/// -------
///
/// ~~~cpp
/// auto font = smk::Font("./arial.ttf", 32);
///
/// [...]
///
/// auto text = smk::Text(font, "The SMK library can draw text");
///
/// text.SetPosition(300,300);
/// text.SetColor(smk::Color::White);
///
/// window.Draw(text);
/// ~~~
class Text : public Transformable {
 public:
  Text();
  Text(Font& font);
  Text(Font& font, const std::string& text);
  Text(Font& font, const std::wstring& text);
  virtual ~Text() = default;

  void SetString(const std::wstring& wide_string);
  void SetString(const std::string& string);
  void SetFont(Font& font);

  void Draw(RenderTarget& target, RenderState state) const override;

  glm::vec2 ComputeDimensions() const;

  Text(Text&&) = default;
  Text(const Text&) = default;
  Text& operator=(Text&&) noexcept = default;
  Text& operator=(const Text&) = default;

 public:
  Font* font_ = nullptr;
  std::wstring string_;
};

}  // namespace smk

#endif /* end of include guard: SMK_TEXT_HPP */
