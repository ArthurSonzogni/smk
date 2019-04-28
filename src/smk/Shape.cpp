// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cmath>
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>

namespace smk {

Shape::Shape() = default;
Shape::Shape(VertexArray vertex_array)
    : vertex_array_(std::move(vertex_array)) {}
Shape::Shape(Shape&& o) {
  operator=(std::move(o));
}
void Shape::operator=(Shape&& o) {
  std::swap(vertex_array_, o.vertex_array_);
}

void Shape::Draw(Screen& screen, RenderState state) const {
  state.color *= color();
  state.view *= Transformation();
  state.vertex_array = &vertex_array_;
  state.blend_mode = blend_mode();
  screen.Draw(state);
}

// static
Shape Shape::Line(glm::vec2 a, glm::vec2 b, float thickness) {
  glm::vec2 dt =
      glm::normalize(glm::vec2(b.y - a.y, -b.x + a.x)) * thickness * 0.5f;
  return Shape(VertexArray(std::vector<Vertex>{
      {a + dt, {0.f, 0.f}},
      {b + dt, {1.f, 0.f}},
      {b - dt, {1.f, 1.f}},
      {a + dt, {0.f, 0.f}},
      {b - dt, {1.f, 1.f}},
      {a - dt, {0.f, 1.f}},
  }));
}

// static
Shape Shape::Square() {
  return Shape(VertexArray(std::vector<Vertex>{
      {{0.f, 0.f}, {0.f, 0.f}},
      {{1.f, 0.f}, {1.f, 0.f}},
      {{1.f, 1.f}, {1.f, 1.f}},
      {{0.f, 0.f}, {0.f, 0.f}},
      {{1.f, 1.f}, {1.f, 1.f}},
      {{0.f, 1.f}, {0.f, 1.f}},
  }));
}

// static
Shape Shape::Circle(int subdivisions) {
  std::vector<Vertex> v;
  glm::vec2 p1 = glm::vec2(1.0f, 0.0f);
  glm::vec2 t1 = glm::vec2(0.5f, 0.5f) + 0.5f * p1;
  glm::vec2 zero(0.f, 0.f);
  for (int i = 1; i <= subdivisions; ++i) {
    float a = (2.0 * M_PI * i) / subdivisions;
    glm::vec2 p2 = glm::vec2(cos(a), sin(a));
    glm::vec2 t2 = glm::vec2(0.5, 0.5) + 0.5f * p2;

    v.push_back({zero, zero});
    v.push_back({p1, t1});
    v.push_back({p2, t2});
    p1 = p2;
    t1 = t2;
  }

  return Shape(VertexArray(std::move(v)));
}

}  // namespace smk
