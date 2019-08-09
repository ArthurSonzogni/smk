#include <cmath>
#include <smk/Audio.hpp>
#include <smk/Screen.hpp>
#include <smk/Sound.hpp>
#include <smk/SoundBuffer.hpp>
#include "asset.hpp"

int main() {
  // Init OpenAL.
  smk::Audio audio;

  // Load a sound file.
  auto sound_buffer = smk::SoundBuffer(asset::water_mp3);

  // Create a sound source.
  auto sound = smk::Sound(sound_buffer);
  sound.Play();                   // Start playing audio in a new thread.

  // Display a black screen to the user and wait for the ESC key to be pressed.
  auto screen = smk::Screen(640, 480, "Sound");
  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.LimitFrameRate(5 /* fps */);
  }
  return 0;
}
