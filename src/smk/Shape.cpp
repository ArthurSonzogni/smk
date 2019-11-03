// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cmath>
#include <smk/Shape.hpp>

namespace smk {
namespace Shape {

Transformable Shape(VertexArray vertex_array) {
  Transformable drawable;
  drawable.SetVertexArray(std::move(vertex_array));
  return drawable;
}

Transformable Line(glm::vec2 a, glm::vec2 b, float thickness) {
  glm::vec2 dt =
      glm::normalize(glm::vec2(b.y - a.y, -b.x + a.x)) * thickness * 0.5f;
  return Shape(VertexArray({
      {a + dt, {0.f, 0.f}},
      {b + dt, {1.f, 0.f}},
      {b - dt, {1.f, 1.f}},
      {a + dt, {0.f, 0.f}},
      {b - dt, {1.f, 1.f}},
      {a - dt, {0.f, 1.f}},
  }));
}

Transformable Square() {
  static VertexArray vertex_array;
  if (!vertex_array.size()) {
    vertex_array = VertexArray({
        {{0.f, 0.f}, {0.f, 0.f}},
        {{1.f, 0.f}, {1.f, 0.f}},
        {{1.f, 1.f}, {1.f, 1.f}},
        {{0.f, 0.f}, {0.f, 0.f}},
        {{1.f, 1.f}, {1.f, 1.f}},
        {{0.f, 1.f}, {0.f, 1.f}},
    });
  }

  return Shape(VertexArray(vertex_array));
}

Transformable Circle(float radius) {
  return Circle(radius, 16 + radius * 0.9);
}

Transformable Circle(float radius, int subdivisions) {
  std::vector<Vertex> v;
  glm::vec2 p1 = glm::vec2(1.0f, 0.0f);
  glm::vec2 t1 = glm::vec2(0.5f, 0.5f) + 0.5f * p1;
  glm::vec2 zero(0.f, 0.f);
  for (int i = 1; i <= subdivisions; ++i) {
    float a = (2.0 * M_PI * i) / subdivisions;
    glm::vec2 p2 = glm::vec2(cos(a), sin(a));
    glm::vec2 t2 = glm::vec2(0.5, 0.5) + 0.5f * p2;

    v.push_back({zero, zero});
    v.push_back({radius * p1, t1});
    v.push_back({radius * p2, t2});
    p1 = p2;
    t1 = t2;
  }

  return Shape(VertexArray(std::move(v)));
}

Transformable3D Cube() {
  constexpr float m = -0.5f;
  constexpr float z = +0.f;
  constexpr float p = +0.5f;
  constexpr float l = 0.f;
  constexpr float r = 1.f;
  auto vertex_array = smk::VertexArray({
      {{m, m, p}, {z, z, p}, {l, l}},
      {{p, m, p}, {z, z, p}, {r, l}},
      {{p, p, p}, {z, z, p}, {r, r}},
      {{m, m, p}, {z, z, p}, {l, l}},
      {{p, p, p}, {z, z, p}, {r, r}},
      {{m, p, p}, {z, z, p}, {l, r}},

      {{m, m, m}, {z, z, m}, {l, l}},
      {{p, p, m}, {z, z, m}, {r, r}},
      {{p, m, m}, {z, z, m}, {r, l}},
      {{m, m, m}, {z, z, m}, {l, l}},
      {{m, p, m}, {z, z, m}, {l, r}},
      {{p, p, m}, {z, z, m}, {r, r}},

      {{m, p, m}, {z, p, z}, {l, l}},
      {{m, p, p}, {z, p, z}, {r, l}},
      {{p, p, p}, {z, p, z}, {r, r}},
      {{m, p, m}, {z, p, z}, {l, l}},
      {{p, p, p}, {z, p, z}, {r, r}},
      {{p, p, m}, {z, p, z}, {l, r}},

      {{m, m, m}, {z, m, z}, {l, l}},
      {{p, m, p}, {z, m, z}, {r, r}},
      {{m, m, p}, {z, m, z}, {r, l}},
      {{m, m, m}, {z, m, z}, {l, l}},
      {{p, m, m}, {z, m, z}, {l, r}},
      {{p, m, p}, {z, m, z}, {r, r}},

      {{p, m, m}, {p, z, z}, {l, l}},
      {{p, p, m}, {p, z, z}, {r, l}},
      {{p, p, p}, {p, z, z}, {r, r}},
      {{p, m, m}, {p, z, z}, {l, l}},
      {{p, p, p}, {p, z, z}, {r, r}},
      {{p, m, p}, {p, z, z}, {l, r}},

      {{m, m, m}, {m, z, z}, {l, l}},
      {{m, p, p}, {m, z, z}, {r, r}},
      {{m, p, m}, {m, z, z}, {r, l}},
      {{m, m, m}, {m, z, z}, {l, l}},
      {{m, m, p}, {m, z, z}, {l, r}},
      {{m, p, p}, {m, z, z}, {r, r}},
  });

  Transformable3D transformable;
  transformable.SetVertexArray(std::move(vertex_array));
  return transformable;
}

Transformable3D IcoSphere(int iteration) {
  std::vector<glm::vec3> out = {
    {+1.f, +0.f, +0.f},
    {+0.f, +1.f, +0.f},
    {+0.f, +0.f, +1.f},

    {-1.f, +0.f, +0.f},
    {+0.f, +0.f, -1.f},
    {+0.f, -1.f, +0.f},

    {+0.f, -1.f, +0.f},
    {+1.f, +0.f, +0.f},
    {+0.f, +0.f, +1.f},

    {+0.f, +1.f, +0.f},
    {+0.f, +0.f, -1.f},
    {-1.f, +0.f, +0.f},

    {-1.f, +0.f,  +0.f},
    {+0.f, -1.f,  +0.f},
    {+0.f, +0.f,  +1.f},

    {+1.f,+0.f,  +0.f},
    {+0.f,+0.f,  -1.f},
    {+0.f,+1.f,  +0.f},

    {+0.f,+1.f,  +0.f},
    {-1.f,+0.f,  +0.f},
    {+0.f,+0.f,  +1.f},

    {+0.f,-1.f,  +0.f},
    {+0.f,+0.f,  -1.f},
    {+1.f,+0.f,  +0.f},
  };

  std::vector<glm::vec3> in;
  for(int i = 0; i<iteration; ++i) {
    in = std::move(out);
    for(unsigned int j = 0; j<in.size();) {
      glm::vec3& a = in[j++];
      glm::vec3& b = in[j++];
      glm::vec3& c = in[j++];
      glm::vec3 d = glm::normalize(a + b + c);
      auto addition = {a, b, d, b, c, d, c, a, d};
      out.insert(out.end(), addition.begin(), addition.end());
    }
  }

  std::vector<Vertex3D> vertex_array;
  for (auto& it : out) {
    vertex_array.push_back(
        {it * 0.5f, it, {it.x * 0.5f + 0.5f, it.y * 0.5f + 0.5f}});
  }

  Transformable3D transformable;
  transformable.SetVertexArray(std::move(vertex_array));
  return transformable;
}

Transformable3D Plane() {
  constexpr float m = -0.5f;
  constexpr float z = +0.f;
  constexpr float p = +0.5f;
  constexpr float l = 0.f;
  constexpr float r = 1.f;
  auto vertex_array = smk::VertexArray({
      {{m, m, z}, {z, z, p}, {l, l}},
      {{p, m, z}, {z, z, p}, {r, l}},
      {{p, p, z}, {z, z, p}, {r, r}},
      {{m, m, z}, {z, z, p}, {l, l}},
      {{p, p, z}, {z, z, p}, {r, r}},
      {{m, p, z}, {z, z, p}, {l, r}},
  });

  Transformable3D transformable;
  transformable.SetVertexArray(std::move(vertex_array));
  return transformable;
}

}  // namespace Shape
}  // namespace smk
