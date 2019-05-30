// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SHAPE_HPP
#define SMK_SHAPE_HPP

#include <smk/Drawable.hpp>
#include <smk/VertexArray.hpp>

namespace smk {
namespace Shape {

Drawable Line(glm::vec2 a, glm::vec2 b, float thickness);
Drawable Square();
Drawable Circle(float radius);
Drawable Circle(float radius, int subdivisions);

}  // namespace Shape
}  // namespace smk

#endif /* end of include guard: SMK_SHAPE_HPP */
