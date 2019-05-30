#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>

int main() {
  // Open a new window.
  auto screen = smk::Screen(640, 480, "test");

  // Create circle_red.
  auto circle_red = smk::Shape::Circle(200);
  circle_red.SetColor(smk::Color::Red);
  circle_red.SetPosition(320,240);

  // Create circle_blue.
  auto circle_blue = smk::Shape::Circle(100, 5 /* subdivision */);
  circle_blue.SetColor(smk::Color::Blue);
  circle_blue.SetPosition(320+200,240);

  // Create line.
  auto line = smk::Shape::Line({0, 0},      // start
                               {150, 100},  // end
                               10           // thickness)
  );
  line.SetColor(smk::Color::Yellow);
  line.Move(200, 200);

  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);

    screen.Draw(circle_red);
    screen.Draw(circle_blue);
    screen.Draw(line);

    screen.Display();
    screen.LimitFrameRate(60 /* fps */);
  }
  return 0;
}
