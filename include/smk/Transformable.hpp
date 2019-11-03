// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_TRANSFORMABLE
#define SMK_TRANSFORMABLE

#include <smk/Drawable.hpp>
#include <smk/RenderState.hpp>

namespace smk {
struct Texture;
class Screen;
class VertexArray;

class TransformableBase : public Drawable {
 public:
  // Tranformation.
  virtual glm::mat4 Transformation() const = 0;

  // Color
  void SetColor(const glm::vec4& color);
  const glm::vec4& color() const { return color_; }

  // Texture
  void SetTexture(const Texture& texture);
  const Texture* texture() const { return texture_; }

  // BlendMode
  void SetBlendMode(const BlendMode&);
  const BlendMode& blend_mode() const { return blend_mode_; }

  // VertexArray
  void SetVertexArray(VertexArray vertex_array);
  const VertexArray* vertex_array() const { return &vertex_array_; }

  // Drawable override
  virtual void Draw(Screen& screen, RenderState state) const override;

  // Movable-copyable class.
  TransformableBase() = default;
  TransformableBase(TransformableBase&&) = default;
  TransformableBase(const TransformableBase&) = default;
  TransformableBase& operator=(TransformableBase&&) = default;
  TransformableBase& operator=(const TransformableBase&) = default;

 private:
  glm::vec4 color_ = {1.0, 1.0, 1.0, 1.0};
  const Texture* texture_ = nullptr;
  BlendMode blend_mode_;
  VertexArray vertex_array_;
};

class Transformable : public TransformableBase {
 public:
  virtual ~Transformable() = default;

  // Center
  void SetCenter(float center_x, float center_y);
  void SetCenter(glm::vec2);

  // Position
  void Move(glm::vec2 move);
  void Move(float move_x, float move_y);
  void SetPosition(float position_x, float position_y);
  void SetPosition(glm::vec2 position);

  // Rotation
  void Rotate(float rotation);
  void SetRotation(float rotation);

  // Scale
  void SetScale(glm::vec2 scale);
  void SetScale(float scale_x, float scale_y);
  void SetScaleX(float scale_x);
  void SetScaleY(float scale_y);

  // Transformable override;
  glm::mat4 Transformation() const override;

  // Movable-copyable class.
  Transformable() = default;
  Transformable(Transformable&&) = default;
  Transformable(const Transformable&) = default;
  Transformable& operator=(Transformable&&) = default;
  Transformable& operator=(const Transformable&) = default;

 private:
  float rotation_ = 0.f;
  glm::vec2 center_ = {0.f, 0.f};
  glm::vec2 position_ = {0.f, 0.f};
  glm::vec2 scale_ = {1.0, 1.0};
};

class Transformable3D : public TransformableBase {
 public:
  virtual ~Transformable3D() = default;

  void SetTransformation(const glm::mat4);
  glm::mat4 Transformation() const override;

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
