// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_TRANSFORMABLE
#define SMK_TRANSFORMABLE

#include <smk/Drawable.hpp>
#include <smk/RenderState.hpp>

namespace smk {
struct Texture;
class RenderTarget;
class VertexArray;

/// A Drawable object supporting several transformations:
/// - Translation
/// - Rotation.
/// - Color filtering.
/// - Modify blending mode. @see smk::BlendMode.
class TransformableBase : public Drawable {
 public:
  // Tranformation.
  virtual glm::mat4 transformation() const = 0;

  /// Color
  void SetColor(const glm::vec4& color);
  const glm::vec4& color() const { return color_; }

  // Texture
  void SetTexture(Texture texture);
  const Texture& texture() const { return texture_; }

  // BlendMode
  void SetBlendMode(const BlendMode&);
  const BlendMode& blend_mode() const { return blend_mode_; }

  // VertexArray
  void SetVertexArray(VertexArray vertex_array);
  const VertexArray& vertex_array() const { return vertex_array_; }

  // Drawable override
  void Draw(RenderTarget& target, RenderState state) const override;

  // Movable-copyable class.
  TransformableBase() = default;
  TransformableBase(TransformableBase&&) noexcept = default;
  TransformableBase(const TransformableBase&) = default;
  TransformableBase& operator=(TransformableBase&&) noexcept = default;
  TransformableBase& operator=(const TransformableBase&) = default;

 private:
  glm::vec4 color_ = {1.0, 1.0, 1.0, 1.0};
  Texture texture_;
  BlendMode blend_mode_ = BlendMode::Alpha;
  VertexArray vertex_array_;
};

/// A 2D Drawable object supporting several transformations:
/// - Translation
/// - Rotation.
/// - Color filtering.
/// - Modify blending mode. @see smk::BlendMode.
class Transformable : public TransformableBase {
 public:
  virtual ~Transformable() = default;

  // Center
  void SetCenter(float center_x, float center_y);
  void SetCenter(const glm::vec2& center);

  // Position
  void Move(const glm::vec2& move);
  void Move(float x, float y);
  void SetPosition(float x, float y);
  void SetPosition(const glm::vec2& position);

  // Rotation
  void Rotate(float rotation);
  void SetRotation(float rotation);

  // Scale
  void SetScale(float scale);
  void SetScale(const glm::vec2& scale);
  void SetScale(float scale_x, float scale_y);
  void SetScaleX(float scale_x);
  void SetScaleY(float scale_y);

  // Transformable override;
  glm::mat4 transformation() const override;

  // Movable-copyable class.
  Transformable() = default;
  Transformable(Transformable&&) noexcept = default;
  Transformable(const Transformable&) = default;
  Transformable& operator=(Transformable&&) = default;
  Transformable& operator=(const Transformable&) = default;

 private:
  float rotation_ = 0.f;
  glm::vec2 center_ = {0.f, 0.f};
  glm::vec2 position_ = {0.f, 0.f};
  glm::vec2 scale_ = {1.0, 1.0};
};

/// A 2D Drawable object supporting several transformations:
/// - Translation
/// - Rotation.
/// - Color filtering.
/// - Modify blending mode. @see smk::BlendMode.
class Transformable3D : public TransformableBase {
 public:
  virtual ~Transformable3D() = default;

  void SetTransformation(const glm::mat4& mat);
  glm::mat4 transformation() const override;

  // Movable-copyable class.
  Transformable3D() = default;
  Transformable3D(Transformable3D&&) = default;
  Transformable3D(const Transformable3D&) = default;
  Transformable3D& operator=(Transformable3D&&) = default;
  Transformable3D& operator=(const Transformable3D&) = default;

 private:
  glm::mat4 transformation_ = glm::mat4(1.f);
};

using Transformable = Transformable;

}  // namespace smk

#endif /* end of include guard: SMK_TRANSFORMABLE */
