#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include "asset.hpp"

#include <iostream>

int main() {
  auto screen = smk::Screen(100, 100, "smk/example/sprite");
  auto texture = smk::Texture(asset::hero_png);
  auto sprite = smk::Sprite(texture);

  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);
    screen.Draw(sprite);
    screen.Display();
    screen.LimitFrameRate(60);
  }
  return 0;
}
