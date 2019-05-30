// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <glm/gtc/matrix_transform.hpp>
#include <smk/Drawable.hpp>
#include <smk/Texture.hpp>
#include <smk/Screen.hpp>

namespace smk {

void Drawable::SetRotation(float rotation) {
  rotation_ = rotation;
}

void Drawable::Rotate(float rotation) {
  rotation_ += rotation;
}

void Drawable::SetPosition(glm::vec2 position) {
  position_ = position;
}

void Drawable::SetPosition(float position_x, float position_y) {
  position_.x = position_x;
  position_.y = position_y;
}

void Drawable::SetCenter(glm::vec2 center) {
  center_ = center;
}

void Drawable::SetCenter(float center_x, float center_y) {
  center_.x = center_x;
  center_.y = center_y;
}

void Drawable::SetScale(glm::vec2 scale) {
  scale_ = scale;
}

void Drawable::SetScale(float scale_x, float scale_y) {
  scale_.x = scale_x;
  scale_.y = scale_y;
}

void Drawable::SetScaleX(float scale_x) {
  scale_.x = scale_x;
}

void Drawable::SetScaleY(float scale_y) {
  scale_.y = scale_y;
}

void Drawable::Move(glm::vec2 move) {
  position_ += move;
}

void Drawable::Move(float move_x, float move_y) {
  position_.x += move_x;
  position_.y += move_y;
}

glm::mat4 Drawable::Transformation() const {
  glm::mat4 ret = glm::mat4(1.0);
  ret = glm::translate(ret, glm::vec3(position_.x, position_.y, 0.0));
  ret = glm::rotate(ret, -rotation_ / 360.f * 2.f * 3.1415f,
                    glm::vec3(0.0, 0.0, 1.0));
  ret = glm::translate(
      ret, glm::vec3(-center_.x * scale_.x, -center_.y * scale_.y, 0.f));
  ret = glm::scale(ret, glm::vec3(scale_.x, scale_.y, 1.0));
  return ret;
}

void Drawable::SetColor(const glm::vec4& color) {
  color_ = color;
}

void Drawable::SetBlendMode(const BlendMode& blend_mode) {
  blend_mode_ = blend_mode;
}

void Drawable::SetTexture(const Texture& texture) {
  texture_ = &texture;
}

void Drawable::SetVertexArray(VertexArray vertex_array) {
  vertex_array_ = std::move(vertex_array);
}

void Drawable::Draw(Screen& screen, RenderState state) const {
  state.color *= color();
  state.texture = texture();
  state.view *= Transformation();
  state.vertex_array = vertex_array();
  state.blend_mode = blend_mode();
  screen.Draw(state);
}

}  // namespace smk
