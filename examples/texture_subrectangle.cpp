#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include "asset.hpp"

#include <iostream>

int main() {
  auto screen = smk::Screen(100, 100, "smk/example/texture_subrectangle");
  auto texture = smk::Texture(asset::hero_png);

  auto sprite_full = smk::Sprite(texture);
  auto sprite_subpart = smk::Sprite(texture);
  sprite_subpart.SetTextureRectangle({5, 5, 25, 25});
  sprite_subpart.Move(35,5);

  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);
    screen.Draw(sprite_full);
    screen.Draw(sprite_subpart);
    screen.Display();
    screen.LimitFrameRate(60);
  }
  return 0;
}
