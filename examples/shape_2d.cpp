#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

int main() {
  // Open a new window.
  auto window = smk::Window(640, 480, "test");

  // Create circle_red.
  auto circle_red = smk::Shape::Circle(200);
  circle_red.SetColor(smk::Color::Red);
  circle_red.SetPosition(320, 240);

  // Create circle_blue.
  auto circle_blue = smk::Shape::Circle(100, 5 /* subdivision */);
  circle_blue.SetColor(smk::Color::Blue);
  circle_blue.SetPosition(320 + 200, 240);

  // Create line.
  auto line = smk::Shape::Line({0, 0},      // start
                               {150, 100},  // end
                               10           // thickness)
  );

  line.SetColor(smk::Color::Yellow);
  line.Move(200, 200);

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    window.Draw(circle_red);
    window.Draw(circle_blue);
    window.Draw(line);

    window.Display();
  });
  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
