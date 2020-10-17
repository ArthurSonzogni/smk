#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Input.hpp>
#include <smk/Text.hpp>
#include <smk/Vibrate.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

int main() {
  auto window = smk::Window(300, 300, "Vibrate");
  auto font = smk::Font(asset::arial_ttf, 34);
  auto text = smk::Text(font, "Touch to vibrate");
  text.SetPosition(10, 10);

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    window.Draw(text);
    window.Display();

    // Vibrate on cursor released.
    if (window.input().IsCursorReleased())
      smk::Vibrate(30 /* ms */);
  });

  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
