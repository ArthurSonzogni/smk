#include <smk/Color.hpp>
#include <smk/Sprite.hpp>
#include <smk/Texture.hpp>
#include <smk/Window.hpp>
#include "./util.hpp"  // ExecuteMainLoop
#include "asset.hpp"

int main() {
  auto window = smk::Window(100, 100, "smk/example/sprite");
  auto texture = smk::Texture(asset::hero_png);
  auto sprite = smk::Sprite(texture);

  ExecuteMainLoop(window, [&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    window.Draw(sprite);
    window.Display();
  });

  return EXIT_SUCCESS;
}
