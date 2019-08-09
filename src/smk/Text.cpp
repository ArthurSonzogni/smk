// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <codecvt>
#include <iostream>
#include <locale>
#include <smk/Font.hpp>
#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <vector>

namespace smk {

std::wstring to_wstring(const std::string& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(s);
}

Text::Text(const Font& font) {
  SetFont(font);
}

Text::Text(const Font& font, const std::string& text) : Text(font) {
  SetString(text);
}

Text::Text(const Font& font, const std::wstring& text) : Text(font) {
  SetString(text);
}

void Text::SetString(const std::wstring& s) {
  string_ = s;
}

void Text::SetString(const std::string& s) {
  string_ = to_wstring(s);
}

void Text::SetFont(const Font& font) {
  font_ = &font;
}

void Text::Draw(Screen& screen, RenderState state) const {
  state.color *= color();
  state.view *= Transformation();
  Sprite sprite;
  float advance_x = 0.f;
  float advance_y = font_->size();
  for (const auto& it : string_) {
    if (it == U'\n') {
      advance_x = 0.f;
      advance_y += font_->size();
      continue;
    }
    auto character = font_->GetCharacter(it);
    if (!character)
      continue;

    if (character->texture.id) {
      sprite.SetPosition(advance_x + character->bearing.x,
                         advance_y + character->bearing.y);
      sprite.SetTexture(character->texture);
      sprite.Draw(screen, state);
    }
    advance_x += character->advance;
  }
}

glm::vec2 Text::ComputeDimensions() const {
  glm::vec2 dimension(0.f, 0.f);
  float advance_x = 0.f;
  float advance_y = font_->size();
  dimension.y += font_->size();
  for (const auto& it : string_) {
    if (it == U'\n') {
      advance_x = 0.f;
      advance_y += font_->size();
      dimension.y += font_->size();
      continue;
    }
    auto character = font_->GetCharacter(it);
    if (!character)
      continue;
    advance_x += character->advance;

    dimension.x = std::max(dimension.x, advance_x);
  }
  return dimension;
}

}  // namespace smk
