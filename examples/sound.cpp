#include <cmath>
#include <smk/Audio.hpp>
#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Screen.hpp>
#include <smk/Sound.hpp>
#include <smk/SoundBuffer.hpp>
#include <smk/Text.hpp>
#include "./util.hpp"  // ExecuteMainLoop
#include "asset.hpp"

int main() {
  // Init OpenAL.
  smk::Audio audio;

  // Display a black screen with a "Click me" button.
  auto screen = smk::Screen(160, 54, "Sound");
  auto font = smk::Font(asset::arial_ttf, 34);
  auto text = smk::Text(font, "Click me");
  text.SetPosition(10,10);

  // Load a sound file.
  auto sound_buffer = smk::SoundBuffer(asset::water_mp3);

  // Create a sound source.
  auto sound = smk::Sound(sound_buffer);

  ExecuteMainLoop([&] {
    screen.PoolEvents();

    // Toggle sound.
    if (screen.input().IsMouseReleased(GLFW_MOUSE_BUTTON_1)) {
      if (sound.is_playing()) {
        sound.Stop();
      } else {
        sound.Play();
      }
    }

    screen.Clear(smk::Color::Black);
    text.SetColor(sound.is_playing() ? smk::Color::White: smk::Color::Red);
    screen.Draw(text);
    screen.Display();

    LimitFrameRate(screen);
  });

  return EXIT_SUCCESS;
}
