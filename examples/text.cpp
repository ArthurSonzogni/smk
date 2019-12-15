#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Text.hpp>
#include <smk/Font.hpp>
#include "asset.hpp"
#include "./util.hpp"  // ExecuteMainLoop

int main() {
  auto screen = smk::Screen(640, 640, "smk/example/text");
  auto font = smk::Font(asset::arial_ttf, 34);

  float step = 0;
  ExecuteMainLoop(screen, [&] {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);

    smk::Text text;
    text.SetFont(font);
    text.SetString("The SMK library can display fonts!!!");
    text.SetPosition(10,10);
    screen.Draw(text);

    text.SetCenter(text.ComputeDimensions() * 0.5f); 
    text.SetRotation(step++);
    text.SetPosition({320.f,320.f});
    screen.Draw(text);

    screen.Display();
  });

  return EXIT_SUCCESS;
}
