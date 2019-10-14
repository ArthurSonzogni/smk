// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SHAPE_HPP
#define SMK_SHAPE_HPP

#include <smk/Transformable.hpp>
#include <smk/VertexArray.hpp>

namespace smk {
namespace Shape {

Transformable Line(glm::vec2 a, glm::vec2 b, float thickness);
Transformable Square();
Transformable Circle(float radius);
Transformable Circle(float radius, int subdivisions);

Transformable3D Cube();
Transformable3D IcoSphere(int interation);
Transformable3D Plane();

}  // namespace Shape
}  // namespace smk

#endif /* end of include guard: SMK_SHAPE_HPP */
