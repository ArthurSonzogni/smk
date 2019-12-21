#include <smk/BlendMode.hpp>
#include <smk/Color.hpp>
#include <smk/Framebuffer.hpp>
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>
#include <smk/Sprite.hpp>
#include "./util.hpp"  // ExecuteMainLoop

int main() {
  int dim = 1024;
  int center = dim / 2;
  auto screen = smk::Screen(dim, dim, "test");

  auto framebuffer_1 = smk::Framebuffer(dim, dim);
  auto framebuffer_2 = smk::Framebuffer(dim, dim);

  auto circle = smk::Shape::Circle(dim * 0.15);

  ExecuteMainLoop(screen, [&] {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);

    auto sprite = smk::Sprite(framebuffer_1);
    sprite.SetBlendMode(smk::BlendMode::Add);
    sprite.SetCenter(center, center);
    sprite.SetPosition(center, center);

    screen.Draw(sprite);
    screen.Display();

    sprite.SetColor({0.2f, 0.5f, 0.9f, 1.f});

    framebuffer_2.Clear(smk::Color::Black);

    // Top
    sprite.SetPosition(center, center - center * 0.5);
    sprite.SetScale(0.5, 0.5);
    framebuffer_2.Draw(sprite);

    // Bottom left
    sprite.SetPosition(center - center * 0.5, center + center * 0.5);
    sprite.SetScale(0.5, 0.5);
    framebuffer_2.Draw(sprite);

    // Bottom right
    sprite.SetPosition(center + center * 0.5, center + center * 0.5);
    sprite.SetScale(0.5, 0.5);
    framebuffer_2.Draw(sprite);

    // Persistence.
    //sprite.SetPosition(center, center);
    //sprite.SetScale(1.f, 1.f);
    //sprite.SetColor({1.f, 1.f, 1.f, 0.2});
    //framebuffer_2.Draw(sprite);

    // Mouse
    circle.SetPosition(screen.input().mouse());
    framebuffer_2.Draw(circle);

    std::swap(framebuffer_1, framebuffer_2);
  });
  return EXIT_SUCCESS;
}
