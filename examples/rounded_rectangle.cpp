#include <algorithm>
#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

int main() {
  auto window = smk::Window(640, 480, "test");

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    smk::View view;
    view.SetCenter(window.dimensions() * 0.5f);
    view.SetSize(window.dimensions());
    window.SetView(view);

    float radius = std::min(window.width(), window.height()) * 0.5 *
                   (0.5 + 0.5 * sin(window.time() * 4.0));
    float margin = 40.f;
    auto rounded_rectangle = smk::Shape::RoundedRectangle(
        window.width() - margin, window.height() - margin, radius);
    rounded_rectangle.SetColor(smk::Color::Red);
    rounded_rectangle.Move(window.dimensions() * 0.5f);
    window.Draw(rounded_rectangle);

    window.Display();
  });
  return EXIT_SUCCESS;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
