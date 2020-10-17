#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

int main() {
  // Open a new window.
  auto window = smk::Window(640, 480, "test");

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::RGB(0.1f, 0.1f, 0.1f));

    float y = 0.5f + 0.4f * sin(window.time());

    // Draw a bezier path
    auto bezier = smk::Shape::Bezier(
        {
            {10, 10},
            {630 * y, 10},
            {10, 480 * y},
            {630, 480 * y},
        },
        50);

    auto bezier_path_foreground = smk::Shape::Path(bezier, 10);
    auto bezier_path_background = smk::Shape::Path(bezier, 20);

    bezier_path_background.SetColor(smk::Color::Black);
    bezier_path_foreground.SetColor(smk::Color::Yellow);

    window.Draw(bezier_path_background);
    window.Draw(bezier_path_foreground);

    window.Display();
  });
  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
