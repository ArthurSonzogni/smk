#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Text.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

int main() {
  auto window = smk::Window(640, 640, "smk/example/text");
  auto font = smk::Font(asset::arial_ttf, 48);

  const float margin = 20.f;

  float step = 0;
  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    // Draw a fixed text.
    auto text = smk::Text(font, "The SMK library\ncan display fonts!!!");
    text.SetPosition(margin, margin);
    window.Draw(text);

    // Draw a rotating text.
    text = smk::Text(font, L"The SMK library\ncan display fonts!!! ←↑→↓");
    text.SetCenter(text.ComputeDimensions() * 0.5f);  // Center
    text.SetPosition({320.f, 320.f});
    text.SetRotation(step++);
    window.Draw(text);

    window.Display();
  });

  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
