// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Font.hpp>

#include <ft2build.h>
#include <iostream>
#include <vector>
#include FT_FREETYPE_H

namespace smk {

Font::Character* Font::GetCharacter(wchar_t c) {
  // Load from cache.
  {
    auto character = characters_.find(c);
    if (character != characters_.end())
      return character->second.get();
  }

  // Load from file.
  if (size_)
  {
    LoadCharacters({c});
    auto character = characters_.find(c);
    if (character != characters_.end())
      return character->second.get();
  }

  // Fallback.
  return nullptr;
}

void Font::operator=(Font&& other) {
  characters_.insert(std::make_move_iterator(begin(other.characters_)),
                     std::make_move_iterator(end(other.characters_)));
  filename_ = other.filename_;
  size_ = other.size_;
}

Font::Font(const std::string& filename, int size)
    : filename_(filename), size_(size) {
  std::vector<wchar_t> preloaded_characters;
  for (wchar_t c = 0; c < 256; ++c)
    preloaded_characters.push_back(c);
  LoadCharacters(preloaded_characters);
}

void Font::LoadCharacters(const std::vector<wchar_t>& chars) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    std::cerr << "SMK > FreeType: Could not init FreeType Library"
              << std::endl;
  }

  FT_Face face;
  if (FT_New_Face(ft, filename_.c_str(), 0, &face)) {
    std::cerr << "SMK > FreeType: Failed to load" << filename_ << std::endl;
  }

  FT_Set_Pixel_Sizes(face, 0, size_);
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
    std::cerr << "ERROR::FREETYTPE: Failed to load Glyph for file " << filename_
              << std::endl;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Disable byte-alignment restriction

  for (auto c : chars) {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::wcout << L"SMK > FreeType: Failed to load Glyph: \"" << c << "\""
                 << std::endl;
      continue;
    }

    int width = face->glyph->bitmap.width;
    int height = face->glyph->bitmap.rows;
    auto character = std::make_unique<Character>();
    character->bearing =
        glm::ivec2(+face->glyph->bitmap_left, -face->glyph->bitmap_top);
    character->advance = face->glyph->advance.x / (64.0f);

    if (width * height != 0) {
      std::vector<uint8_t> buffer_rgba(width * height * 4);
      {
        int j = 0;
        for (int i = 0; i < width * height; ++i) {
          const uint8_t v = face->glyph->bitmap.buffer[i];
          buffer_rgba[j++] = 255;
          buffer_rgba[j++] = 255;
          buffer_rgba[j++] = 255;
          buffer_rgba[j++] = v;
        }
      }
      character->texture = smk::Texture(buffer_rgba.data(), width, height);
    }

    characters_[c] = std::move(character);
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

}  // namespace smk
