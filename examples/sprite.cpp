#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include "asset.hpp"

#include <iostream>

struct Player {
 public:
  static smk::Texture texture;
  Player(int x, int y) : x(x), y(y) {}
  void Step() {
    x += dx;
    
    // Bounce against the walls.
    if (x >= 640 - texture.width / 2)
      dx = -dx;
    if (x <= texture.width / 2)
      dx = -dx;
  }

  void Draw(smk::Screen& screen) {
    smk::Sprite sprite;
    sprite.SetTexture(texture);
    sprite.SetPosition({x, y});
    sprite.SetCenter(texture.width / 2.0, 0.f);
    sprite.SetScale(dx > 0 ? 1.0 : -1.0, 1.0);
    screen.Draw(sprite);
  }

 private:
  int x;
  int y;
  int dx = 1.0;
};
smk::Texture Player::texture;

int main() {
  auto screen = smk::Screen(640, 32*3, "smk/example/sprite");
  Player::texture = smk::Texture(asset::hero_png); // Defined after screen.

  std::vector<Player> players = {Player(320, 0), Player(32, 32), Player(624, 64)};

  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    for (auto& player : players)
      player.Step();

    screen.Clear(smk::Color::Black);
    for (auto& player : players)
      player.Draw(screen);
    screen.Display();
    screen.LimitFrameRate(60 /* fps */);
  }
  return 0;
}
