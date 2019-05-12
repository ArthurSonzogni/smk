#include <smk/Screen.hpp>
#include <smk/SoundBuffer.hpp>
#include <smk/Sound.hpp>
#include <cmath>
#include "asset.hpp"

int main() {
  auto sound_buffer = smk::SoundBuffer(asset::water_mp3);
  auto sound = smk::Sound();
  sound.SetBuffer(sound_buffer);
  sound.Play();

  auto screen = smk::Screen(640, 480, "Sound");
  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.LimitFrameRate(5 /* fps */);
  }
  return 0;
}
