#include <glm/gtc/matrix_transform.hpp>
#include <smk/Color.hpp>
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>
#include <smk/Texture.hpp>
#include <smk/Transformable.hpp>
#include <smk/VertexArray.hpp>
#include "asset.hpp"

int random(int& r, int modulo) {
  return (r = (r * 68152648) % 9876541) % modulo;
}

int main() {
  // Open a new window.
  auto screen = smk::Screen(640, 480, "test");
  screen.SetShaderProgram(screen.shader_program_3d());

  auto cube = smk::Shape::Cube();
  auto sphere = smk::Shape::IcoSphere(6);

  auto texture = smk::Texture(asset::hero_png);
  cube.SetTexture(texture);
  sphere.SetTexture(texture);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  float animation = 0.f;
  float animation_df = 0.2f;
  float time = 0.f;

  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    screen.PoolEvents();
    screen.Clear(smk::Color::Black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    animation += animation_df;
    animation_df -= animation*0.0005;
    time += 0.1f;

    screen.SetView(glm::perspective(
        70.f, float(screen.width()) / screen.height(), 0.1f, 100.f));

    // Draw the cube.
    {
      glm::mat4 v(1.f);
      v = glm::translate(v, {-2.f, -2.f, -10.f});
      v = glm::rotate(v, animation, {0.f, 1.f, 0.f});
      cube.SetTransformation(v);
      screen.Draw(cube);
    }

    // Draw the spheres
    {
      glm::mat4 view(1.f);
      view = glm::translate(view, {-2.f, -1.f, -10.f-0.5f * animation});
      view = glm::scale(view, {0.4f, 0.4f, 0.4f});

      for (int i = 1; i < 27; ++i) {
        view = view * glm::translate(glm::mat4(1.0), {1.0, 0.0, 0.0});
        view = glm::rotate(view, 0.03f * i * animation * 0.1f, {0.0, 0.0, 1.0});
        sphere.SetTransformation(
            glm::rotate(view, animation * (i % 2 - 0.5f), {0.0, 0.0, 1.0}));
        screen.Draw(sphere);
      }
    }

    screen.Display();
    screen.LimitFrameRate(60 /* fps */);
  }
  return 0;
}
