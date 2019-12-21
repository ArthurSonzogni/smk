// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SPRITE_HPP
#define SMK_SPRITE_HPP

#include <smk/Rectangle.hpp>
#include <smk/RenderState.hpp>
#include <smk/Texture.hpp>
#include <smk/Transformable.hpp>

namespace smk {

class Framebuffer;

// A Drawable specialised in displaying rectangular texture.
class Sprite : public Transformable {
 public:
  Sprite() = default;
  Sprite(const Texture& texture);
  Sprite(const Framebuffer& framebuffer);

  void SetTexture(const Texture& texture);
  void SetFramebuffer(const Framebuffer& framebuffer);

  // Useful to display a sub part of the texture.
  void SetTextureRectangle(const Rectangle& rectangle);

  Sprite(Sprite&&) = default;
  Sprite(const Sprite&) = default;
  Sprite& operator=(Sprite&&) = default;
  Sprite& operator=(const Sprite&) = default;
};

}  // namespace smk

#endif /* end of include guard: SMK_SPRITE_HPP */
