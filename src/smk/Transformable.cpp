// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <glm/gtc/matrix_transform.hpp>
#include <smk/RenderTarget.hpp>
#include <smk/Texture.hpp>
#include <smk/Transformable.hpp>

namespace smk {

void Transformable::SetRotation(float rotation) {
  rotation_ = rotation;
}

void Transformable::Rotate(float rotation) {
  rotation_ += rotation;
}

void Transformable::SetPosition(glm::vec2 position) {
  position_ = position;
}

void Transformable::SetPosition(float position_x, float position_y) {
  position_.x = position_x;
  position_.y = position_y;
}

void Transformable::SetCenter(glm::vec2 center) {
  center_ = center;
}

void Transformable::SetCenter(float center_x, float center_y) {
  center_.x = center_x;
  center_.y = center_y;
}

void Transformable::SetScale(glm::vec2 scale) {
  scale_ = scale;
}

void Transformable::SetScale(float scale_x, float scale_y) {
  scale_.x = scale_x;
  scale_.y = scale_y;
}

void Transformable::SetScaleX(float scale_x) {
  scale_.x = scale_x;
}

void Transformable::SetScaleY(float scale_y) {
  scale_.y = scale_y;
}

void Transformable::Move(glm::vec2 move) {
  position_ += move;
}

void Transformable::Move(float move_x, float move_y) {
  position_.x += move_x;
  position_.y += move_y;
}

glm::mat4 Transformable::Transformation() const {
  glm::mat4 ret = glm::mat4(1.0);
  ret = glm::translate(ret, {position_.x, position_.y, 0.0});
  ret = glm::rotate(ret, -rotation_ * (2.f * 3.1415f / 360.f), {0.0, 0.0, 1.0});
  ret =
      glm::translate(ret, {-center_.x * scale_.x, -center_.y * scale_.y, 0.f});
  ret = glm::scale(ret, {scale_.x, scale_.y, 1.0});
  return ret;
}

void TransformableBase::SetColor(const glm::vec4& color) {
  color_ = color;
}

void TransformableBase::SetBlendMode(const BlendMode& blend_mode) {
  blend_mode_ = blend_mode;
}

void TransformableBase::SetTexture(Texture texture) {
  texture_ = std::move(texture);
}

void TransformableBase::SetVertexArray(VertexArray vertex_array) {
  vertex_array_ = std::move(vertex_array);
}

void TransformableBase::Draw(RenderTarget& target, RenderState state) const {
  state.color *= color();
  state.texture = texture();
  state.view *= Transformation();
  state.vertex_array = vertex_array();
  state.blend_mode = blend_mode();
  target.Draw(state);
}

void Transformable3D::SetTransformation(const glm::mat4 transformation) {
  transformation_ = transformation;
}

glm::mat4 Transformable3D::Transformation() const {
  return transformation_;
}

}  // namespace smk
