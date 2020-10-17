// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SHAPE_HPP
#define SMK_SHAPE_HPP

#include <glm/glm.hpp>
#include <smk/Transformable.hpp>
#include <smk/VertexArray.hpp>

/// @example shape_2d.cpp
/// @example shape_3d.cpp
/// @example bezier.cpp
/// @example rounded_rectangle.cpp

namespace smk {

/// A collection of static function to build simple shape.
class Shape {
 public:
  static Transformable FromVertexArray(VertexArray vertex_array);
  static Transformable Line(const glm::vec2& a,
                            const glm::vec2& b,
                            float thickness);
  static Transformable Square();
  static Transformable Circle(float radius);
  static Transformable Circle(float radius, int subdivisions);
  static Transformable Path(const std::vector<glm::vec2>& points,
                            float thickness);
  static Transformable RoundedRectangle(float width,
                                        float height,
                                        float radius);
  static Transformable3D Cube();
  static Transformable3D IcoSphere(int interation);
  static Transformable3D Plane();
  static std::vector<glm::vec2> Bezier(const std::vector<glm::vec2>& point,
                                       size_t subdivision);
};

}  // namespace smk

#endif /* end of include guard: SMK_SHAPE_HPP */
