// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Font.hpp>

#include <ft2build.h>
#include <iostream>
#include <vector>
#include FT_FREETYPE_H

namespace smk {

const float super_resolution = 1.0;

Font::Character* Font::GetCharacter(wchar_t c) const {
  auto character = characters_.find(c);
  if (character == characters_.end())
    return nullptr;
  else
    return character->second.get();
}

void Font::operator=(Font&& other) {
  characters_.insert(std::make_move_iterator(begin(other.characters_)),
                     std::make_move_iterator(end(other.characters_)));
  size_ = other.size_;
}

// static
Font::Font(const std::string& filename, int size) {
  size_ = size;
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
              << std::endl;

  FT_Face face;
  if (FT_New_Face(ft, filename.c_str(), 0, &face)) {
    std::cout << "ERROR::FREETYPE: Failed to load" << filename << std::endl;
  }

  FT_Set_Pixel_Sizes(face, 0, size_ * super_resolution);
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
    std::cout << "ERROR::FREETYTPE: Failed to load Glyph for file " << filename
              << std::endl;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Disable byte-alignment restriction

  for (wchar_t c = 0; c < 256; c++) {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }

    int width = face->glyph->bitmap.width;
    int height = face->glyph->bitmap.rows;
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

    auto character = std::make_unique<Character>();
    character->texture.width = width;
    character->texture.height = height;
    character->bearing =
        glm::ivec2(+face->glyph->bitmap_left / super_resolution,
                   -face->glyph->bitmap_top / super_resolution);
    character->advance = face->glyph->advance.x / (64.0f * super_resolution);


    // Generate texture
    glGenTextures(1, &character->texture.id);
    glBindTexture(GL_TEXTURE_2D, character->texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, buffer_rgba.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    character->texture.width /= super_resolution;
    character->texture.height /= super_resolution;

    characters_[c] = std::move(character);
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

}  // namespace smk
