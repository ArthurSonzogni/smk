#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Transformable.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Window.hpp>

int main() {
  // Open a new window.
  auto window = smk::Window(640, 480, "test");

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    // Draw traces.
    for (const auto& it : window.input().touches()) {
      const auto& touch = it.second;
      for (int i = 1; i < touch.data_points.size(); ++i) {
        glm::vec2 p1 = touch.data_points[i - 1].position;
        glm::vec2 p2 = touch.data_points[i - 0].position;

        auto line = smk::Shape::Line(p1, p2, 2);
        window.Draw(line);
      }
    }

    window.Display();
  });
  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
