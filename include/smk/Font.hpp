// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_FONT_HPP
#define SMK_FONT_HPP

#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <smk/OpenGL.hpp>
#include <smk/Texture.hpp>
#include <string>
#include <vector>

namespace smk {

class Font {
 public:
  Font() = default;  // Empty font.
  Font(const std::string& filename, int size);

  int size() const { return size_; }

  struct Character {
    smk::Texture texture;
    glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
    float advance;       // Offset to advance to next glyph
  };
  Character* GetCharacter(wchar_t) const;
  void LoadCharacters(const std::vector<wchar_t>& chars);

  // --- Move only resource ----------------------------------------------------
  Font(Font&&) = default;
  Font(const Font&) = delete;
  void operator=(Font&&);
  void operator=(const Font&) = delete;
  // ---------------------------------------------------------------------------

 private:
  std::map<wchar_t, std::unique_ptr<Character>> characters_;
  std::string filename_;
  int size_ = 0;
};

}  // namespace smk

#endif /* end of include guard: SMK_FONT_HPP */
