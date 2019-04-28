// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_TEXT_HPP
#define SMK_TEXT_HPP

#include <string>
#include <smk/Drawable.hpp>
#include <smk/Texture.hpp>

namespace smk {
class Font;

class Text : public Drawable {
 public:
  void SetString(const std::wstring&);
  void SetString(const std::string&);
  void SetFont(const Font& font);
  void Draw(Screen& screen, RenderState state) const;

  glm::vec2 ComputeDimensions() const;

 public:
  const Font* font_ = nullptr;
  std::wstring string_;
};

} // namespace smk

#endif /* end of include guard: SMK_TEXT_HPP */
