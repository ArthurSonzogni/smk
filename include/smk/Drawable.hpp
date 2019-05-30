// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_DRAWABLE_HPP
#define SMK_DRAWABLE_HPP

#include <smk/RenderState.hpp>

namespace smk {
struct Texture;
class Screen;
class VertexArray;

class Drawable {
 public:
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
  glm::mat4 Transformation() const;

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

  void Draw(Screen& screen, RenderState state) const;
  
  // Move only class.
  Drawable() = default;
  Drawable(Drawable&&) = default;
  Drawable(const Drawable&) = delete;
  Drawable& operator=(Drawable&&) = default;
  Drawable& operator=(const Drawable&) = delete;

 private:
  glm::vec2 center_ = {0.f, 0.f};
  glm::vec2 position_ = {0.f, 0.f};
  glm::vec2 scale_ = {1.0, 1.0};
  glm::vec4 color_ = {1.0, 1.0, 1.0, 1.0};
  float rotation_ = 0.f;
  const Texture* texture_ = nullptr;
  BlendMode blend_mode_;
  VertexArray vertex_array_;
};

}  // namespace smk

#endif /* end of include guard: SMK_DRAWABLE_HPP */
