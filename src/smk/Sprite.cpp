// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/OpenGL.hpp>
#include <smk/Shader.hpp>
#include <smk/Sprite.hpp>
#include <smk/VertexArray.hpp>
#include <vector>

namespace smk {

void Sprite::SetTexture(const Texture& texture) {
  Drawable::SetTexture(texture);
  SetTextureRectangle({0.f, 0.f, float(texture.width), float(texture.height)});
}

void Sprite::SetTextureRectangle(const Rectangle& rectangle) {
  float l = rectangle.left / texture()->width;
  float r = rectangle.right / texture()->width;
  float t = rectangle.top / texture()->height;
  float b = rectangle.bottom / texture()->height;
  float www = rectangle.width();
  float hhh = rectangle.height();
  SetVertexArray(VertexArray(std::vector<Vertex>({
      {{0.f, 0.f}, {l, t}},
      {{0.f, www}, {l, b}},
      {{hhh, www}, {r, b}},
      {{0.f, 0.f}, {l, t}},
      {{hhh, www}, {r, b}},
      {{hhh, 0.f}, {r, t}},
  })));
}

}  // namespace smk
