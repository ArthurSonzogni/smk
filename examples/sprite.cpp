#include <smk/Color.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

int main() {
  auto window = smk::Window(100, 100, "smk/example/sprite");
  auto texture = smk::Texture(asset::hero_png);
  auto sprite = smk::Sprite(texture);

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    window.Draw(sprite);
    window.Display();
  });

  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
