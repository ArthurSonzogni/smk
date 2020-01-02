// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Text.hpp>
#include <smk/Vibrate.hpp>
#include <smk/Window.hpp>
#include "./util.hpp"  // ExecuteMainLoop
#include "asset.hpp"

int main() {
  auto window = smk::Window(300, 300, "Vibrate");
  auto font = smk::Font(asset::arial_ttf, 34);
  auto text = smk::Text(font, "Touch to vibrate");
  text.SetPosition(10, 10);

  ExecuteMainLoop(window, [&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    window.Draw(text);
    window.Display();

    // Toggle sound.
    if (window.input().IsCursorReleased())
      smk::Vibrate(30 /* ms */);
  });

  return EXIT_SUCCESS;
}
