// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SPRITE_HPP
#define SMK_SPRITE_HPP

#include <smk/Drawable.hpp>
#include <smk/Rectangle.hpp>
#include <smk/RenderState.hpp>
#include <smk/Screen.hpp>
#include <smk/Texture.hpp>

namespace smk {

// A Drawable specialised in displaying rectangular texture.
class Sprite : public Drawable {
 public:
  void SetTexture(const Texture& texture);

  // Useful to display a sub part of the texture.
  void SetTextureRectangle(const Rectangle& rectangle);

  Sprite() = default;
  Sprite(Sprite&&) = default;
  Sprite(const Sprite&) = delete;
  Sprite& operator=(Sprite&&) = default;
  Sprite& operator=(const Sprite&) = delete;
};

}  // namespace smk

#endif /* end of include guard: SMK_SPRITE_HPP */
