#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>

int main() {
  auto screen = smk::Screen(640, 480, "test");
  auto circle = smk::Shape::Circle(64);
  circle.SetScale(200,200);
  circle.SetColor(smk::Color::Red);
  circle.SetPosition(320,240);

  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);
    screen.Draw(circle);
    screen.Display();
    screen.LimitFrameRate(60 /* fps */);
  }
  return 0;
}
