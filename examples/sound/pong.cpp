#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>
#include <smk/BlendMode.hpp>
#include <cmath>

int main() {
  auto screen = smk::Screen(640, 480, "pong");

  auto player_shape = smk::Shape::Square();
  player_shape.SetScale(100,10);
  player_shape.SetColor(smk::Color::Red);

  glm::vec2 ball_position = {340, 240};
  glm::vec2 ball_speed = {1.0, 1.0};

  while(!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);

    auto mouse = screen.input().mouse();

    player_shape.SetPosition(mouse.x-50, 460);
    screen.Draw(player_shape);

    screen.Display();
    screen.LimitFrameRate(60.f);
  }
}
