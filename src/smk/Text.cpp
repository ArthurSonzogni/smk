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

// From UTF8 encoded string |input|, eat in between 1 and 4 byte representing
// one codepoint. Put the codepoint into |ucs|. Start at |start| and update
// |end| to represent the beginning of the next byte to eat for consecutive
// executions.
bool EatCodePoint(const std::string& input,
                  size_t start,
                  size_t* end,
                  uint32_t* ucs) {
  if (start >= input.size()) {
    *end = start + 1;
    return false;
  }
  const uint8_t C0 = input[start];

  // 1 byte string.
  if ((C0 & 0b1000'0000) == 0b0000'0000) {  // NOLINT
    *ucs = C0 & 0b0111'1111;                // NOLINT
    *end = start + 1;
    return true;
  }

  // 2 byte string.
  if ((C0 & 0b1110'0000) == 0b1100'0000 &&  // NOLINT
      start + 1 < input.size()) {
    const uint8_t C1 = input[start + 1];
    *ucs = 0;
    *ucs += C0 & 0b0001'1111;  // NOLINT
    *ucs <<= 6;                // NOLINT
    *ucs += C1 & 0b0011'1111;  // NOLINT
    *end = start + 2;
    return true;
  }

  // 3 byte string.
  if ((C0 & 0b1111'0000) == 0b1110'0000 &&  // NOLINT
      start + 2 < input.size()) {
    const uint8_t C1 = input[start + 1];
    const uint8_t C2 = input[start + 2];
    *ucs = 0;
    *ucs += C0 & 0b0000'1111;  // NOLINT
    *ucs <<= 6;                // NOLINT
    *ucs += C1 & 0b0011'1111;  // NOLINT
    *ucs <<= 6;                // NOLINT
    *ucs += C2 & 0b0011'1111;  // NOLINT
    *end = start + 3;
    return true;
  }

  // 4 byte string.
  if ((C0 & 0b1111'1000) == 0b1111'0000 &&  // NOLINT
      start + 3 < input.size()) {
    const uint8_t C1 = input[start + 1];
    const uint8_t C2 = input[start + 2];
    const uint8_t C3 = input[start + 3];
    *ucs = 0;
    *ucs += C0 & 0b0000'0111;  // NOLINT
    *ucs <<= 6;                // NOLINT
    *ucs += C1 & 0b0011'1111;  // NOLINT
    *ucs <<= 6;                // NOLINT
    *ucs += C2 & 0b0011'1111;  // NOLINT
    *ucs <<= 6;                // NOLINT
    *ucs += C3 & 0b0011'1111;  // NOLINT
    *end = start + 4;
    return true;
  }

  *end = start + 1;
  return false;
}


/// Convert a std::wstring into a UTF8 std::string.
std::wstring to_wstring(const std::string& s) {
  std::wstring out;

  size_t i = 0;
  uint32_t codepoint = 0;
  while (EatCodePoint(s, i, &i, &codepoint)) {
    // On linux wstring are UTF32 encoded:
    if constexpr (sizeof(wchar_t) == 4) {
      out.push_back(codepoint);  // NOLINT
      continue;
    }

    // On Windows, wstring are UTF16 encoded:

    // Codepoint encoded using 1 word:
    // NOLINTNEXTLINE
    if (codepoint < 0xD800 || (codepoint > 0xDFFF && codepoint < 0x10000)) {
      uint16_t p0 = codepoint;  // NOLINT
      out.push_back(p0);        // NOLINT
      continue;
    }

    // Codepoint encoded using 2 words:
    codepoint -= 0x010000;                               // NOLINT
    uint16_t p0 = (((codepoint << 12) >> 22) + 0xD800);  // NOLINT
    uint16_t p1 = (((codepoint << 22) >> 22) + 0xDC00);  // NOLINT
    out.push_back(p0);                                   // NOLINT
    out.push_back(p1);                                   // NOLINT
  }
  return out;
}

/// Construct a null Text. It can't be drawn.
Text::Text() = default;

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

    auto* character = font_->FetchGlyph(it);
    if (!character) {
      continue;
    }

    if (character->texture.id()) {
      const float x = advance_x + float(character->bearing.x);
      const float y = advance_y + float(character->bearing.y);
      const float w = float(character->texture.width());
      const float h = float(character->texture.height());
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
  dimension.y += font_->line_height();
  for (const auto& it : string_) {
    if (it == U'\n') {
      advance_x = 0.f;
      dimension.y += font_->line_height();
      continue;
    }
    auto* character = font_->FetchGlyph(it);
    if (!character) {
      continue;
    }
    advance_x += character->advance;

    dimension.x = std::max(dimension.x, advance_x);
  }
  return dimension;
}

}  // namespace smk
