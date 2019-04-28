// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/OpenGL.hpp>
#include <smk/Shader.hpp>
#include <smk/Sprite.hpp>
#include <smk/VertexArray.hpp>
#include <vector>

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

namespace smk {

static Texture white_texture;
Texture* WhiteTexture() {
  if (white_texture.id == 0) {
    white_texture.width = 1;
    white_texture.height = 1;
    const uint8_t data[4] = {255, 255, 255, 255};
    glGenTextures(1, &white_texture.id);
    glBindTexture(GL_TEXTURE_2D, white_texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, white_texture.width,
                 white_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
  }
  return &white_texture;
}

void Sprite::Draw(Screen& screen, RenderState state) const {
  state.color *= color();
  state.texture = texture();
  state.view *= Transformation();
  state.vertex_array = screen.square_vertex_array();
  state.blend_mode = blend_mode();
  screen.Draw(state);
}

}  // namespace smk
