#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Texture.hpp>
#include <smk/Transformable.hpp>
#include <smk/VertexArray.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

int random(int& r, int modulo) {
  return (r = (r * 68152648) % 9876541) % modulo;
}

int main() {
  // Open a new window.
  auto window = smk::Window(640, 480, "test");
  window.SetShaderProgram(window.shader_program_3d());
  window.shader_program_3d().SetUniform("light_position",
                                        glm::vec4(0.f, 5.f, 0.f, 1.f));

  auto cube = smk::Shape::Cube();
  auto sphere = smk::Shape::IcoSphere(6);

  auto texture = smk::Texture(asset::hero_png);
  cube.SetTexture(texture);
  sphere.SetTexture(texture);

  float animation = 0.f;
  float animation_df = 0.2f;
  float time = 0.f;

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    animation += animation_df;
    animation_df -= animation * 0.0005;
    time += 0.1f;

    window.SetView(glm::perspective(
        70.f, float(window.width()) / window.height(), 0.1f, 100.f));

    // Draw the cube.
    {
      glm::mat4 v(1.f);
      v = glm::translate(v, {-2.f, -2.f, -10.f});
      v = glm::rotate(v, animation, {0.f, 1.f, 0.f});
      cube.SetTransformation(v);
      window.Draw(cube);
    }

    // Draw the spheres
    {
      glm::mat4 view(1.f);
      view = glm::translate(view, {-2.f, -1.f, -10.f - 0.5f * animation});
      view = glm::scale(view, {0.4f, 0.4f, 0.4f});

      for (int i = 1; i < 27; ++i) {
        view = view * glm::translate(glm::mat4(1.0), {1.0, 0.0, 0.0});
        view = glm::rotate(view, 0.03f * i * animation * 0.1f, {0.0, 0.0, 1.0});
        sphere.SetTransformation(
            glm::rotate(view, animation * (i % 2 - 0.5f), {0.0, 0.0, 1.0}));
        window.Draw(sphere);
      }
    }

    window.Display();
  });

  return EXIT_SUCCESS;
}

// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
