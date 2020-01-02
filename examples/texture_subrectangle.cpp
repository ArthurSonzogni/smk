// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Color.hpp>
#include <smk/Window.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include "asset.hpp"
#include "./util.hpp"  // ExecuteMainLoop

#include <iostream>

int main() {
  auto window = smk::Window(100, 100, "smk/example/texture_subrectangle");
  auto texture = smk::Texture(asset::hero_png);

  auto sprite_full = smk::Sprite(texture);
  auto sprite_subpart = smk::Sprite(texture);
  sprite_subpart.SetTextureRectangle({5, 5, 25, 25});
  sprite_subpart.Move(35,5);

  ExecuteMainLoop(window, [&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    window.Draw(sprite_full);
    window.Draw(sprite_subpart);
    window.Display();
  });

  return EXIT_SUCCESS;
}
