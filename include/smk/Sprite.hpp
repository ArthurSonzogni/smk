// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SPRITE_HPP
#define SMK_SPRITE_HPP

#include "Drawable.hpp"
#include <smk/Texture.hpp>
#include <smk/RenderState.hpp>
#include <smk/Screen.hpp>

namespace smk {

class Sprite : public Drawable {
 public:
  ~Sprite() override = default;
  void Draw(Screen& screen, RenderState state) const override;
};

}  // namespace smk

#endif /* end of include guard: SMK_SPRITE_HPP */
