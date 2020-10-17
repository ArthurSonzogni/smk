#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Input.hpp>
#include <smk/Text.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

int main() {
  auto window = smk::Window(640, 64, "smk/example/text");
  auto& input = window.input();
  auto font = smk::Font(asset::arial_ttf, 34);
  auto character_listener = input.MakeCharacterListener();

  std::wstring user_input;

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    wchar_t character;
    while (character_listener->Receive(&character))
      user_input += character;

    if (input.IsKeyReleased(GLFW_KEY_BACKSPACE) && !user_input.empty())
      user_input.erase(user_input.size() - 1);

    auto text = smk::Text(font, L"Input = " + user_input);
    text.SetPosition(10, 10);
    window.Draw(text);

    window.Display();
  });

  return EXIT_SUCCESS;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
