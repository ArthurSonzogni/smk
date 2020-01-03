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

class Text : public Transformable {
 public:
  Text() = default;
  Text(Font& font);
  Text(Font& font, const std::string& text);
  Text(Font& font, const std::wstring& text);
  virtual ~Text() = default;

  void SetString(const std::wstring&);
  void SetString(const std::string&);
  void SetFont(Font& font);

  virtual void Draw(RenderTarget& target, RenderState state) const override;

  glm::vec2 ComputeDimensions() const;

  Text(Text&&) = default;
  Text(const Text&) = default;
  Text& operator=(Text&&) = default;
  Text& operator=(const Text&) = default;

 public:
  Font* font_ = nullptr;
  std::wstring string_;
};

}  // namespace smk

#endif /* end of include guard: SMK_TEXT_HPP */
