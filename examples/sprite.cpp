#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include "asset.hpp"

#include <iostream>

int main() {
  auto screen = smk::Screen(100, 100, "smk/example/sprite");
  auto texture = smk::Texture(asset::hero_png);
  auto sprite = smk::Sprite();
  sprite.SetTexture(texture);
  auto s1 = sprite;
  auto s2 = s1;
  auto s3 = s2;
  auto s4 = s3;
  auto s5 = s4;
  auto s6 = s5;
  auto s7 = s6;
  auto s8 = s7;
  auto s9 = s8;
  auto s10 = s9;
  sprite = s10;

  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
  auto s1 = sprite;
  auto s2 = s1;
  auto s3 = s2;
  auto s4 = s3;
  auto s5 = s4;
  auto s6 = s5;
  auto s7 = s6;
  auto s8 = s7;
  auto s9 = s8;
  auto s10 = s9;
  sprite = s10;
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);
    screen.Draw(sprite);
    screen.Display();
    screen.LimitFrameRate(60);
  }
  return 0;
}
