// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SHAPE_HPP
#define SMK_SHAPE_HPP

#include <smk/Transformable.hpp>
#include <smk/VertexArray.hpp>

/// @example shape_2d.cpp
/// @example shape_3d.cpp

namespace smk {

/// A collection of static function to build simple shape.
class Shape {
 public:
  static Transformable Line(glm::vec2 a, glm::vec2 b, float thickness);
  static Transformable Square();
  static Transformable Circle(float radius);
  static Transformable Circle(float radius, int subdivisions);
  static Transformable FromVertexArray(VertexArray vertex_array);
  static Transformable3D Cube();
  static Transformable3D IcoSphere(int interation);
  static Transformable3D Plane();
};

}  // namespace smk

#endif /* end of include guard: SMK_SHAPE_HPP */
