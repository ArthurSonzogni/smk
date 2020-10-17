// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <algorithm>
#include <codecvt>
#include <iostream>
#include <locale>
#include <smk/Font.hpp>
#include <smk/RenderTarget.hpp>
#include <smk/Text.hpp>
#include <smk/VertexArray.hpp>
#include <vector>

namespace smk {

std::wstring to_wstring(const std::string& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(s);
}

/// Construct a null Text. It can't be drawn.
Text::Text() {}

/// @brief Constructor.
/// @param font The Font to be used for drawing glyphs.
Text::Text(Font& font) {
  SetFont(font);
}

/// @brief Constructor.
/// @param font The Font to be used for drawing glyphs.
/// @param text The character string to be drawn.
Text::Text(Font& font, const std::string& text) : Text(font) {
  SetString(text);
}

/// @brief Constructor.
/// @param font The Font to be used for drawing glyphs.
/// @param text The character string to be drawn.
Text::Text(Font& font, const std::wstring& text) : Text(font) {
  SetString(text);
}

/// Update the text to be drawn.
void Text::SetString(const std::wstring& wide_string) {
  string_ = wide_string;
}

/// Update the text to be drawn.
void Text::SetString(const std::string& string) {
  string_ = to_wstring(string);
}

/// Update the Font to be used.
void Text::SetFont(Font& font) {
  font_ = &font;
}

/// Draw the Text to the screen.
void Text::Draw(RenderTarget& target, RenderState state) const {
  state.color *= color();
  glm::mat4 transformation = state.view * this->transformation();
  float advance_x = 0.f;
  float advance_y = font_->baseline_position();

  state.vertex_array = VertexArray(std::vector<Vertex>({
      {{0.f, 0.f}, {0.f, 0.f}},
      {{0.f, 1.f}, {0.f, 1.f}},
      {{1.f, 1.f}, {1.f, 1.f}},
      {{0.f, 0.f}, {0.f, 0.f}},
      {{1.f, 1.f}, {1.f, 1.f}},
      {{1.f, 0.f}, {1.f, 0.f}},
  }));

  for (const auto& it : string_) {
    if (it == U'\n') {
      advance_x = 0.f;
      advance_y += font_->line_height();
      continue;
    }

    auto character = font_->FetchGlyph(it);
    if (!character)
      continue;

    if (character->texture.id()) {
      const float x = advance_x + character->bearing.x;
      const float y = advance_y + character->bearing.y;
      const float w = character->texture.width();
      const float h = character->texture.height();
      state.texture = character->texture;
      state.view = transformation * glm::mat4(w, 0.f, 0.f, 0.f,    //
                                              0.f, h, 0.f, 0.f,    //
                                              0.f, 0.f, 1.f, 0.f,  //
                                              x, y, 0.f, 1.f       //
                                    );

      target.Draw(state);
    }
    advance_x += character->advance;
  }
}

/// Compute the dimension of the text when drawn to the screen.
/// @return a tuple (width,height).
glm::vec2 Text::ComputeDimensions() const {
  glm::vec2 dimension(0.f, 0.f);
  float advance_x = 0.f;
  float advance_y = font_->line_height();
  dimension.y += font_->line_height();
  for (const auto& it : string_) {
    if (it == U'\n') {
      advance_x = 0.f;
      advance_y += font_->line_height();
      dimension.y += font_->line_height();
      continue;
    }
    auto character = font_->FetchGlyph(it);
    if (!character)
      continue;
    advance_x += character->advance;

    dimension.x = std::max(dimension.x, advance_x);
  }
  return dimension;
}

}  // namespace smk
