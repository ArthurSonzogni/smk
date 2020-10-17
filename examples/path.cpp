#include <smk/Color.hpp>
#include <smk/Input.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

int main() {
  // Open a new window.
  auto window = smk::Window(512, 512, "test");

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::RGB(0.1f, 0.1f, 0.1f));

    float angle = window.time();
    glm::vec2 rot = 50.f * glm::vec2(cos(angle), sin(angle));
    std::vector<glm::vec2> points = {
        glm::vec2(256 - 100, 256 - 100) + rot,
        glm::vec2(256 - 100, 256 - 100),
        glm::vec2(256 + 100, 256 - 100),
        glm::vec2(256 + 100, 256 + 100),
        window.input().cursor(),
    };

    auto path_white = smk::Shape::Path(points, 30);
    auto path_black = smk::Shape::Path(points, 5);

    path_black.SetColor({0.f, 0.f, 0.f, 1.f});

    window.Draw(path_white);
    window.Draw(path_black);

    window.Display();
  });
  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
