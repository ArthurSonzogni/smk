#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Input.hpp>
#include <smk/Text.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

int main() {
  auto window = smk::Window(480, 96, "smk/example/scroll");
  auto font = smk::Font(asset::arial_ttf, 34);

  auto scroll_sum = glm::vec2(0.f, 0.f);
  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    scroll_sum += window.input().scroll_offset();

    window.Clear(smk::Color::Black);
    std::string x_scroll = std::to_string(scroll_sum.x);
    std::string y_scroll = std::to_string(scroll_sum.y);
    auto text = smk::Text(font, "dx = " + x_scroll + "\n" + "dy = " + y_scroll);
    window.Draw(text);

    window.Display();
  });
  return EXIT_SUCCESS;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
