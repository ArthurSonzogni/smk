#include <iostream>
#include <smk/Color.hpp>
#include <smk/Font.hpp>
#include <smk/Input.hpp>
#include <smk/Shader.hpp>
#include <smk/Text.hpp>
#include <smk/Window.hpp>

#include "asset.hpp"

const char* kVertexShader = R"(
  layout(location = 0) in vec2 space_position;
  layout(location = 1) in vec2 texture_position;

  uniform mat4 projection;
  uniform mat4 view;

  out vec2 f_texture_position;

  void main() {
    f_texture_position = texture_position;
    gl_Position = projection * view * vec4(space_position, 0.0, 1.0);
  }
)";

const char* kFragmentShader = R"(
  in vec2 f_texture_position;
  uniform sampler2D texture_0;
  uniform vec4 color;
  uniform float time;
  out vec4 out_color;

  vec3 hsv(vec3 c)
  {
      vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
      vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
      return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
  }

  void main() {
    float hue = (f_texture_position.y + time) * 0.5f;
    hue = fract(hue);
    out_color.rgb = hsv(vec3(hue, 1.0, 1.0));

    out_color.a = texture(texture_0, f_texture_position).a;
  }
)";

int main() {
  auto window = smk::Window(640, 640, "smk/example/text");
  auto font = smk::Font(asset::arial_ttf, 48);

  const float margin = 20.f;

  smk::Shader vertex_shader;
  smk::Shader fragment_shader;
  smk::ShaderProgram program;

  auto step = [&] {
    program.SetUniform("time", window.time());

    // Wait until the user click on the screen.
    if (!window.input().IsCursorPressed())
      return;

    // Compile the shaders.
    vertex_shader = smk::Shader::FromString(kVertexShader, GL_VERTEX_SHADER);

    fragment_shader =
        smk::Shader::FromString(kFragmentShader, GL_FRAGMENT_SHADER);

    // Link the shaders into a program.
    program = smk::ShaderProgram();
    program.AddShader(vertex_shader);
    program.AddShader(fragment_shader);
    program.Link();

    // Check for errors:
    if (!program.LinkStatus())
      exit(EXIT_FAILURE);

    window.SetShaderProgram(program);
  };

  auto draw = [&] {
    auto text = smk::Text(font, "Click to synchronously\ncompile a new shader");
    text.SetPosition(margin, margin);
    window.Draw(text);
  };

  window.ExecuteMainLoop([&] {
    window.PoolEvents();
    window.Clear(smk::Color::Black);

    step();
    draw();

    window.Display();
  });

  return EXIT_SUCCESS;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
