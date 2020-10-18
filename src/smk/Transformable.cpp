// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <glm/gtc/matrix_transform.hpp>
#include <smk/RenderTarget.hpp>
#include <smk/Texture.hpp>
#include <smk/Transformable.hpp>

namespace smk {

/// @brief Set the rotation to apply before drawing the object.
/// @see Transformable::Rotate.
/// @param rotation The angle in radian.
void Transformable::SetRotation(float rotation) {
  rotation_ = rotation;
}

/// @brief Increase the rotation of the object to apply before drawing it.
/// @see Transformable::SetRotation.
/// @param rotation The delta of rotation to be added.
void Transformable::Rotate(float rotation) {
  rotation_ += rotation;
}

/// @brief Set the position of the object to be drawn.
/// @see Transformable::Move.
/// @param position the position (x,y) of the object.
void Transformable::SetPosition(const glm::vec2& position) {
  position_ = position;
}

/// @brief Set the position of the object to be drawn.
/// @see Transformable::Move.
/// @param x The position along the horizontal axis.
/// @param y The position along the vertical axis.
void Transformable::SetPosition(float x, float y) {
  position_ = {x, y};
}

/// Increase the position of the object being drawn.
/// @see smk::SetPosition
/// @param move The increment of position (x,y)
void Transformable::Move(const glm::vec2& move) {
  position_ += move;
}

/// Increase the position of the object being drawn.
/// @see smk::SetPosition
/// @param x The increment of position along the horizontal axis.
/// @param y The increment of position along the vertical axis.
void Transformable::Move(float x, float y) {
  Move({x, y});
}

/// @brief Set the center of the object. It is used as the rotation center. The
/// center of the object will be drawn exactly on (0,0) on the screen (plus its
/// potential translation if any)
/// @param center The center position (x,y) in the object.
void Transformable::SetCenter(const glm::vec2& center) {
  center_ = center;
}

/// @brief Set the center of the object. It is used as the rotation center. The
/// center of the object will be drawn exactly on (0,0) on the screen (plus its
/// potential translation if any)
/// @param x The center position along the horizontal axis.
/// @param y The center position along the vertical axis.
void Transformable::SetCenter(float x, float y) {
  SetCenter({x, y});
}

/// @brief Increase or decrease the size of the object being drawn.
/// @param scale The ratio of magnification.
void Transformable::SetScale(float scale) {
  SetScale({scale, scale});
}

/// @brief Increase or decrease the size of the object being drawn.
/// @param scale The ratio of magnification.
void Transformable::SetScale(const glm::vec2& scale) {
  scale_ = scale;
}

/// @brief Increase or decrease the size of the object being drawn.
/// @param scale_x The ratio of magnification along the horizontal axis.
/// @param scale_y The ratio of magnification along the vertical axis.
void Transformable::SetScale(float scale_x, float scale_y) {
  scale_.x = scale_x;
  scale_.y = scale_y;
}

/// @brief Increase or decrease the size of the object being drawn.
/// @param scale_x The ratio of magnification along the horizontal axis.
void Transformable::SetScaleX(float scale_x) {
  scale_.x = scale_x;
}

/// @brief Increase or decrease the size of the object being drawn.
/// @param scale_y The ratio of magnification along the vertical axis.
void Transformable::SetScaleY(float scale_y) {
  scale_.y = scale_y;
}

/// @brief Increase or decrease the size of the object being drawn.
/// @return the transformation applied to the object. This is the result of
///         applying the translation, rotation, center and scaling to the the
///         object.
glm::mat4 Transformable::transformation() const {
  glm::mat4 ret = glm::mat4(1.0);
  ret = glm::translate(ret, {position_.x, position_.y, 0.0});
  if (rotation_ != 0.f)
    ret =
        glm::rotate(ret, -rotation_ * (2.f * 3.1415f / 360.f), {0.0, 0.0, 1.0});
  ret =
      glm::translate(ret, {-center_.x * scale_.x, -center_.y * scale_.y, 0.f});
  ret = glm::scale(ret, {scale_.x, scale_.y, 1.0});
  return ret;
}

/// @brief Modify the color of the object. The resulting pixel is the
/// multiplication component wise in between this color and the original pixel
/// color.
/// @param color The color.
void TransformableBase::SetColor(const glm::vec4& color) {
  color_ = color;
}

/// @brief Set the blending mode to be used for drawing the object.
/// @param blend_mode the BlendMode to be used.
void TransformableBase::SetBlendMode(const BlendMode& blend_mode) {
  blend_mode_ = blend_mode;
}

/// Set the object's texture.
void TransformableBase::SetTexture(Texture texture) {
  texture_ = std::move(texture);
}

/// Set the object's shape.
void TransformableBase::SetVertexArray(VertexArray vertex_array) {
  vertex_array_ = std::move(vertex_array);
}

void TransformableBase::Draw(RenderTarget& target, RenderState state) const {
  state.color *= color();
  state.texture = texture();
  state.view *= transformation();
  state.vertex_array = vertex_array();
  state.blend_mode = blend_mode();
  target.Draw(state);
}

/// @brief set the transformation to use for drawing this object, represented as
/// 4x4 matrix.
/// @see https://learnopengl.com/Getting-started/Transformations
/// @param transformation The 4x4 matrix defining the transformation.
void Transformable3D::SetTransformation(const glm::mat4& transformation) {
  transformation_ = transformation;
}

glm::mat4 Transformable3D::transformation() const {
  return transformation_;
}

}  // namespace smk
