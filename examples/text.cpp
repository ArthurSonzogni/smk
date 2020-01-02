// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Color.hpp>
#include <smk/Window.hpp>
#include <smk/Text.hpp>
#include <smk/Font.hpp>
#include "asset.hpp"
#include "./util.hpp"  // ExecuteMainLoop

int main() {
  auto window = smk::Window(640, 640, "smk/example/text");
  auto font = smk::Font(asset::arial_ttf, 34);

  float step = 0;
  ExecuteMainLoop(window, [&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    smk::Text text;
    text.SetFont(font);
    text.SetString("The SMK library can display fonts!!!");
    text.SetPosition(10,10);
    window.Draw(text);

    text.SetCenter(text.ComputeDimensions() * 0.5f); 
    text.SetRotation(step++);
    text.SetPosition({320.f,320.f});
    window.Draw(text);

    window.Display();
  });

  return EXIT_SUCCESS;
}
