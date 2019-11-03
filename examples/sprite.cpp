#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include "./util.hpp"  // ExecuteMainLoop
#include "asset.hpp"

#include <iostream>

int main() {
  auto screen = smk::Screen(100, 100, "smk/example/sprite");
  auto texture = smk::Texture(asset::hero_png);
  auto sprite = smk::Sprite(texture);

  ExecuteMainLoop([&] {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);
    screen.Draw(sprite);
    screen.Display();
    LimitFrameRate(screen);
  });

  return EXIT_SUCCESS;
}
