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

/// @example sprite.cpp
/// @example sprite_move.cpp
/// @example texture_subrectangle.cpp

/// A Drawable specialised in displaying rectangular texture.
///
/// Example:
/// -------
/// ~~~cpp
/// auto sprite = smk::Sprite(texture_ball);
///
/// sprite.SetCenter(32,32);
/// sprite.SetPosition(player.x, player.y);
/// sprite.SetRotation(player.rotation);
///
/// window.Draw(sprite);
/// ~~~
class Sprite : public Transformable {
 public:
  Sprite() = default;
  Sprite(const Texture& texture);
  Sprite(const Texture& texture, const Rectangle rectangle);
  explicit Sprite(Framebuffer& framebuffer);

  // Movable and copyable.
  Sprite(Sprite&&) = default;
  Sprite(const Sprite&) = default;
  Sprite& operator=(Sprite&&) = default;
  Sprite& operator=(const Sprite&) = default;

  // Modify the sprite.
  void SetTexture(const Texture& texture);
  void SetTextureRectangle(const Rectangle& rectangle);
};

}  // namespace smk

#endif /* end of include guard: SMK_SPRITE_HPP */
