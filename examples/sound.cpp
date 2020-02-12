// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cmath>
#include <smk/Audio.hpp>
#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Sound.hpp>
#include <smk/SoundBuffer.hpp>
#include <smk/Text.hpp>
#include <smk/Window.hpp>
#include "asset.hpp"

int main() {
  // Init OpenAL.
  smk::Audio audio;

  // Display a black window with a "Click me" button.
  auto window = smk::Window(160, 54, "Sound");
  auto font = smk::Font(asset::arial_ttf, 34);
  auto text = smk::Text(font, "Click me");
  text.SetPosition(10, 10);

  // Load a sound file.
  auto sound_buffer = smk::SoundBuffer(asset::water_mp3);

  // Create a sound source.
  auto sound = smk::Sound(sound_buffer);

  window.ExecuteMainLoop([&] {
    window.PoolEvents();

    // Toggle sound.
    if (window.input().IsCursorReleased()) {
      if (sound.IsPlaying()) {
        sound.Stop();
      } else {
        sound.Play();
      }
    }

    window.Clear(smk::Color::Black);
    text.SetColor(sound.IsPlaying() ? smk::Color::White : smk::Color::Red);
    window.Draw(text);
    window.Display();
  });

  return EXIT_SUCCESS;
}
