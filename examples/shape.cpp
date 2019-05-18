#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>

int main() {
  // Open a new window.
  auto screen = smk::Screen(640, 480, "test");

  // Create circle by using 64 vertices.
  auto circle = smk::Shape::Circle(64);

  // Scale it so that it has a 200px radius.
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
