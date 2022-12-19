// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <ft2build.h>

#include <iostream>
#include <smk/Font.hpp>
#include <vector>
#include FT_FREETYPE_H

namespace smk {

Font::Glyph* Font::FetchGlyph(wchar_t in) {
  // Load from cache.
  auto character = glyphs_.find(in);
  if (character != glyphs_.end()) {
    return character->second.get();
  }

  // Load from file.
  if (line_height_ == 0.F) {
    LoadGlyphs({in});
    auto character = glyphs_.find(in);
    if (character != glyphs_.end()) {
      return character->second.get();
    }
  }

  // Fallback.
  return nullptr;
}

Font& Font::operator=(Font&& other) noexcept {
  glyphs_.insert(std::make_move_iterator(begin(other.glyphs_)),
                 std::make_move_iterator(end(other.glyphs_)));
  filename_ = other.filename_;
  line_height_ = other.line_height_;
  baseline_position_ = other.baseline_position_;
  return *this;
}

Font::Font(std::string filename, float line_height)
    : filename_(std::move(filename)), line_height_(line_height) {
  std::vector<wchar_t> preloaded_characters;
  const int character_to_preload = 256;
  for (wchar_t c = 0; c < character_to_preload; ++c) {
    preloaded_characters.push_back(c);
  }
  LoadGlyphs(preloaded_characters);
}

void Font::LoadGlyphs(const std::vector<wchar_t>& chars) {
  FT_Library ft = {};
  if (FT_Init_FreeType(&ft)) {
    std::cerr << "SMK > FreeType: Could not init FreeType Library" << std::endl;
  }

  FT_Face face = {};
  if (FT_New_Face(ft, filename_.c_str(), 0, &face)) {
    std::cerr << "SMK > FreeType: Failed to load" << filename_ << std::endl;
  }

  baseline_position_ =
      line_height_ *
      ((float(face->ascender) / float(face->ascender - face->descender)));
  FT_Set_Pixel_Sizes(face, FT_UInt(line_height_), FT_UInt(line_height_));
  // NOLINTNEXTLINE
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
    std::cerr << "ERROR::FREETYTPE: Failed to load Glyph for file " << filename_
              << std::endl;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Disable byte-alignment restriction

  for (auto c : chars) {
    // Load character glyph
    // NOLINTNEXTLINE
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::wcout << L"SMK > FreeType: Failed to load Glyph: \"" << c << "\""
                 << std::endl;
      continue;
    }

    int width = int(face->glyph->bitmap.width);
    int height = int(face->glyph->bitmap.rows);
    auto character = std::make_unique<Glyph>();
    character->bearing =
        glm::ivec2(+face->glyph->bitmap_left, -face->glyph->bitmap_top);
    const float advance_scale = 1.F / 64.F;
    character->advance = float(face->glyph->advance.x) * advance_scale;

    if (width * height != 0) {
      std::vector<uint8_t> buffer_rgba(width * height * 4);
      {
        int j = 0;
        for (int i = 0; i < width * height; ++i) {
          const uint8_t v = face->glyph->bitmap.buffer[i]; // NOLINT
          buffer_rgba[j++] = 255;                          // NOLINT
          buffer_rgba[j++] = 255;                          // NOLINT
          buffer_rgba[j++] = 255;                          // NOLINT
          buffer_rgba[j++] = v;                            // NOLINT
        }
      }
      character->texture =
          smk::Texture(buffer_rgba.data(), width, height);
    }

    glyphs_[c] = std::move(character);
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

}  // namespace smk
