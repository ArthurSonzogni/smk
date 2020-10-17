#include <iostream>
#include <smk/Color.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

struct Player {
 public:
  static smk::Texture texture;
  Player(int x, int y) : x(x), y(y) {}
  void Step() {
    x += dx;

    // Bounce against the walls.
    if (x >= 640 - texture.width() / 2)
      dx = -dx;
    if (x <= texture.width() / 2)
      dx = -dx;
  }

  void Draw(smk::Window& window) {
    smk::Sprite sprite(texture);
    sprite.SetPosition({x, y});
    sprite.SetCenter(texture.width() / 2.0, 0.f);
    sprite.SetScale(dx > 0 ? 1.0 : -1.0, 1.0);
    window.Draw(sprite);
  }

 private:
  int x;
  int y;
  int dx = 1.0;
};
smk::Texture Player::texture;

int main() {
  auto window = smk::Window(640, 32 * 3, "smk/example/sprite");
  Player::texture = smk::Texture(asset::hero_png);  // Defined after window.

  std::vector<Player> players = {Player(320, 0), Player(32, 32),
                                 Player(624, 64)};

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    for (auto& player : players)
      player.Step();

    window.Clear(smk::Color::Black);
    for (auto& player : players)
      player.Draw(window);
    window.Display();
  });

  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
