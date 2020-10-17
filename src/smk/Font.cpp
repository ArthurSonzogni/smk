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
  {
    auto character = glyphs_.find(in);
    if (character != glyphs_.end())
      return character->second.get();
  }

  // Load from file.
  if (line_height_) {
    LoadGlyphs({in});
    auto character = glyphs_.find(in);
    if (character != glyphs_.end())
      return character->second.get();
  }

  // Fallback.
  return nullptr;
}

void Font::operator=(Font&& other) noexcept {
  glyphs_.insert(std::make_move_iterator(begin(other.glyphs_)),
                 std::make_move_iterator(end(other.glyphs_)));
  filename_ = other.filename_;
  line_height_ = other.line_height_;
  baseline_position_ = other.baseline_position_;
}

Font::Font(const std::string& filename, float line_height)
    : filename_(filename), line_height_(line_height) {
  std::vector<wchar_t> preloaded_characters;
  for (wchar_t c = 0; c < 256; ++c)
    preloaded_characters.push_back(c);
  LoadGlyphs(preloaded_characters);
}

void Font::LoadGlyphs(const std::vector<wchar_t>& chars) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    std::cerr << "SMK > FreeType: Could not init FreeType Library" << std::endl;
  }

  FT_Face face;
  if (FT_New_Face(ft, filename_.c_str(), 0, &face)) {
    std::cerr << "SMK > FreeType: Failed to load" << filename_ << std::endl;
  }

  baseline_position_ =
      line_height_ *
      ((float(face->ascender) / (face->ascender - face->descender)));
  FT_Set_Pixel_Sizes(face, line_height_, line_height_);
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
    auto character = std::make_unique<Glyph>();
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

    glyphs_[c] = std::move(character);
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

}  // namespace smk
