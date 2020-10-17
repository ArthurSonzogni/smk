#include <smk/BlendMode.hpp>
#include <smk/Color.hpp>
#include <smk/Framebuffer.hpp>
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Sprite.hpp>
#include <smk/Window.hpp>

int main() {
  int dim = 512;
  int center = dim / 2;
  auto window = smk::Window(dim, dim, "Framebufer example");

  // Two framebuffer. Reading one and writing in the other. Swapping both for
  // every iterations.
  auto framebuffer_1 = smk::Framebuffer(dim, dim);
  auto framebuffer_2 = smk::Framebuffer(dim, dim);

  // Draw a circle under user's mouse.
  auto circle = smk::Shape::Circle(dim * 0.15);

  window.ExecuteMainLoop([&] {
    window.PoolEvents();

    // Use framebuffer_1 to draw into framebuffer_2 and the window -------------
    auto sprite = smk::Sprite(framebuffer_1);
    sprite.SetBlendMode(smk::BlendMode::Add);

    // ----Draw to the window --------------------------------------------------
    window.Clear(smk::Color::Black);
    sprite.SetCenter(center, center);
    sprite.SetPosition(center, center);
    window.Draw(sprite);
    window.Display();

    // ----Draw into framebuffer2 ----------------------------------------------
    framebuffer_2.Clear(smk::Color::Black);
    sprite.SetScale(0.5, 0.5);
    sprite.SetColor({0.6f, 0.7f, 1.f, 1.f});

    // Top triangle
    sprite.SetPosition(center, dim * 0.25);
    framebuffer_2.Draw(sprite);

    // Bottom left triangle.
    sprite.SetPosition(dim * 0.25, dim * 0.75);
    framebuffer_2.Draw(sprite);

    // Bottom right triangle.
    sprite.SetPosition(dim * 0.75, dim * 0.75);
    framebuffer_2.Draw(sprite);

    // Circle under user's mouse.
    circle.SetPosition(window.input().cursor());
    framebuffer_2.Draw(circle);

    // -------------------------------------------------------------------------

    std::swap(framebuffer_1, framebuffer_2);
  });
  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
