// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SHAPE_HPP
#define SMK_SHAPE_HPP

#include "Drawable.hpp"
#include <smk/Drawable.hpp>

namespace smk {

class Shape : public Drawable {
 public:
  Shape();  // Invalid shape.
  Shape(VertexArray vertex_array);
  ~Shape() override = default;
  Shape(const Shape&) = delete;
  Shape(Shape&&);
  void operator=(const Shape&) = delete;
  void operator=(Shape&&);

  static Shape Line(glm::vec2 a, glm::vec2 b, float thickness);
  static Shape Square();
  static Shape Circle(int subdivisions);

  void Draw(Screen&, RenderState) const override;

 private:
  VertexArray vertex_array_;
};

} // namespace smk

#endif /* end of include guard: SMK_SHAPE_HPP */
