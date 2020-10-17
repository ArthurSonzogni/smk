// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <algorithm>
#include <cmath>
#include <smk/Shape.hpp>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

namespace smk {

Transformable Shape::FromVertexArray(VertexArray vertex_array) {
  Transformable drawable;
  drawable.SetVertexArray(std::move(vertex_array));
  return drawable;
}

/// @brief Return a line with a given thickness
/// @param a The first end.
/// @param b Second end.
/// @param thickness This line thickness.
Transformable Shape::Line(const glm::vec2& a,
                          const glm::vec2& b,
                          float thickness) {
  glm::vec2 dt =
      glm::normalize(glm::vec2(b.y - a.y, -b.x + a.x)) * thickness * 0.5f;

  return FromVertexArray(VertexArray({
      {a + dt, {0.f, 0.f}},
      {b + dt, {1.f, 0.f}},
      {b - dt, {1.f, 1.f}},
      {a + dt, {0.f, 0.f}},
      {b - dt, {1.f, 1.f}},
      {a - dt, {0.f, 1.f}},
  }));
}

/// @brief Return the square [0,1]x[0,1]
Transformable Shape::Square() {
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

  return FromVertexArray(vertex_array);
}

/// @brief Return a circle.
/// @param radius The circle'radius.
Transformable Shape::Circle(float radius) {
  return Circle(radius, 16 + radius * 0.9);
}

/// @brief Return a circle.
/// @param radius The circle'radius.
/// @param subdivisions The number of triangles used for drawing the circle.
Transformable Shape::Circle(float radius, int subdivisions) {
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

  return FromVertexArray(VertexArray(std::move(v)));
}

/// @brief Return a centered 1x1x1 3D cube
Transformable3D Shape::Cube() {
  constexpr float m = -0.5f;
  constexpr float z = +0.f;
  constexpr float p = +0.5f;
  constexpr float l = 0.f;
  constexpr float r = 1.f;
  auto vertex_array = smk::VertexArray({
      {{m, m, p}, {z, z, p}, {l, l}}, {{p, m, p}, {z, z, p}, {r, l}},
      {{p, p, p}, {z, z, p}, {r, r}}, {{m, m, p}, {z, z, p}, {l, l}},
      {{p, p, p}, {z, z, p}, {r, r}}, {{m, p, p}, {z, z, p}, {l, r}},

      {{m, m, m}, {z, z, m}, {l, l}}, {{p, p, m}, {z, z, m}, {r, r}},
      {{p, m, m}, {z, z, m}, {r, l}}, {{m, m, m}, {z, z, m}, {l, l}},
      {{m, p, m}, {z, z, m}, {l, r}}, {{p, p, m}, {z, z, m}, {r, r}},

      {{m, p, m}, {z, p, z}, {l, l}}, {{m, p, p}, {z, p, z}, {r, l}},
      {{p, p, p}, {z, p, z}, {r, r}}, {{m, p, m}, {z, p, z}, {l, l}},
      {{p, p, p}, {z, p, z}, {r, r}}, {{p, p, m}, {z, p, z}, {l, r}},

      {{m, m, m}, {z, m, z}, {l, l}}, {{p, m, p}, {z, m, z}, {r, r}},
      {{m, m, p}, {z, m, z}, {r, l}}, {{m, m, m}, {z, m, z}, {l, l}},
      {{p, m, m}, {z, m, z}, {l, r}}, {{p, m, p}, {z, m, z}, {r, r}},

      {{p, m, m}, {p, z, z}, {l, l}}, {{p, p, m}, {p, z, z}, {r, l}},
      {{p, p, p}, {p, z, z}, {r, r}}, {{p, m, m}, {p, z, z}, {l, l}},
      {{p, p, p}, {p, z, z}, {r, r}}, {{p, m, p}, {p, z, z}, {l, r}},

      {{m, m, m}, {m, z, z}, {l, l}}, {{m, p, p}, {m, z, z}, {r, r}},
      {{m, p, m}, {m, z, z}, {r, l}}, {{m, m, m}, {m, z, z}, {l, l}},
      {{m, m, p}, {m, z, z}, {l, r}}, {{m, p, p}, {m, z, z}, {r, r}},
  });

  Transformable3D transformable;
  transformable.SetVertexArray(std::move(vertex_array));
  return transformable;
}

/// @brief A centered sphere
/// @param iteration
///   Control the number of triangle used to make the sphere. It will contain
///   \f$ 8 \time 3^iteration\f$ triangles.
Transformable3D Shape::IcoSphere(int iteration) {
  std::vector<glm::vec3> out = {
      {+1.f, +0.f, +0.f}, {+0.f, +1.f, +0.f}, {+0.f, +0.f, +1.f},
      {-1.f, +0.f, +0.f}, {+0.f, +0.f, -1.f}, {+0.f, -1.f, +0.f},
      {+0.f, -1.f, +0.f}, {+1.f, +0.f, +0.f}, {+0.f, +0.f, +1.f},
      {+0.f, +1.f, +0.f}, {+0.f, +0.f, -1.f}, {-1.f, +0.f, +0.f},
      {-1.f, +0.f, +0.f}, {+0.f, -1.f, +0.f}, {+0.f, +0.f, +1.f},
      {+1.f, +0.f, +0.f}, {+0.f, +0.f, -1.f}, {+0.f, +1.f, +0.f},
      {+0.f, +1.f, +0.f}, {-1.f, +0.f, +0.f}, {+0.f, +0.f, +1.f},
      {+0.f, -1.f, +0.f}, {+0.f, +0.f, -1.f}, {+1.f, +0.f, +0.f},
  };

  std::vector<glm::vec3> in;
  for (int i = 0; i < iteration; ++i) {
    in = std::move(out);
    for (unsigned int j = 0; j < in.size();) {
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

/// @brief Return a centered 1x1 square in a 3D space.
Transformable3D Shape::Plane() {
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

/// @brief Return a bezier curve.
/// @see https://en.wikipedia.org/wiki/Bézier_curve
/// @param points The sequence of control points where the produced curve should
/// pass by.
/// @param subdivision The number of points in the output.
// static
std::vector<glm::vec2> Shape::Bezier(const std::vector<glm::vec2>& points,
                                     size_t subdivision) {
  std::vector<glm::vec2> path;
  for (size_t index = 0; index < subdivision + 1; ++index) {
    std::vector<glm::vec2> data = points;
    float x = float(index) / subdivision;
    while (data.size() >= 2) {
      for (size_t i = 0; i < data.size() - 1; ++i)
        data[i] = glm::mix(data[i], data[i + 1], x);
      data.resize(data.size() - 1);
    }
    path.push_back(data[0]);
  }
  return path;
}

/// @brief Build a path of a given |thickness| along a sequence of connected
/// lines.
/// @params points The sequence of points the path is going through.
/// @params thickness This width of the path.
// static
smk::Transformable Shape::Path(const std::vector<glm::vec2>& points,
                               float thickness) {
  using namespace glm;
  std::vector<glm::vec3> planes_left;
  std::vector<glm::vec3> planes_right;

  thickness *= 0.5f;
  // Compute planes shifted by +/- |thickness| around lines:
  // points[i] -- points[i+1]

  for (size_t i = 1; i < points.size(); ++i) {
    glm::vec3 plane_left =
        cross(vec3(points[i - 1], 1.f), vec3(points[i - 0], 1.f));
    glm::vec3 plane_right = plane_left;
    plane_left.z -= thickness * length(vec2(plane_left.x, plane_left.y));
    plane_right.z += thickness * length(vec2(plane_right.x, plane_right.y));
    planes_left.push_back(plane_left);
    planes_right.push_back(plane_right);
  }

  // Compute the intersection of plane[i] and plane[i+1]. It gives us the the
  // outline of the shape to be filled.
  std::vector<glm::vec2> points_left;
  std::vector<glm::vec2> points_right;

  // Cap begin.
  {
    glm::vec2 direction = normalize(points[1] - points[0]);
    glm::vec2 normal = {direction.y, -direction.x};
    points_left.push_back(points[0] - normal * thickness);
    points_right.push_back(points[0] + normal * thickness);
  }

  float epsilon = 0.01f;
  int i = 0;
  for (size_t j = 1; j < points.size() - 1; ++j) {
    glm::vec3 intersection_left = cross(planes_left[i], planes_left[j]);
    glm::vec3 intersection_right = cross(planes_right[i], planes_right[j]);
    if (intersection_left.z * intersection_right.z < epsilon)
      continue;
    intersection_left /= intersection_left.z;
    intersection_right /= intersection_right.z;
    glm::vec2 left = glm::vec2(intersection_left);
    glm::vec2 right = glm::vec2(intersection_right);
    if (glm::distance(left, right) > 10.f * thickness) {
      glm::vec2 middle = glm::vec2(left + right) * 0.5f;
      glm::vec2 dir = glm::normalize(glm::vec2(right - left)) * 5.f * thickness;
      left = glm::vec3(middle - dir, 1.f);
      right = glm::vec3(middle + dir, 1.f);
    }
    points_left.push_back(left);
    points_right.push_back(right);
    i = j;
  }

  // Cap end.
  {
    glm::vec2 direction = normalize(points[points.size() - 2] - points.back());
    glm::vec2 normal = {direction.y, -direction.x};
    points_left.push_back(points.back() + normal * thickness);
    points_right.push_back(points.back() - normal * thickness);
  }

  std::vector<smk::Vertex> v;

  // Fill using rectangles.
  // ...-A--C-...  A = points_left[i]
  //     |\ | ...  B = points_right[i]
  //     | \| ...  C = points_left[i + 1]
  // ...-B--D-...  D = points_right[i + 1];
  for (size_t i = 1; i < points_left.size(); ++i) {
    glm::vec2& A = points_left[i - 1];
    glm::vec2& B = points_right[i - 1];
    glm::vec2& C = points_left[i];
    glm::vec2& D = points_right[i];

    v.push_back({A, {0.0, 0.0}});
    v.push_back({B, {0.0, 0.0}});
    v.push_back({D, {0.0, 0.0}});
    v.push_back({A, {0.0, 0.0}});
    v.push_back({D, {0.0, 0.0}});
    v.push_back({C, {0.0, 0.0}});
  }

  return smk::Shape::FromVertexArray(smk::VertexArray(std::move(v)));
}

/// @brief Return a rounded centered rectangle.
/// @params width The width of the rectangle.
/// @params height The height of the rectangle.
/// @params radius The radius of the four corners.
smk::Transformable Shape::RoundedRectangle(float width,
                                           float height,
                                           float radius) {
  radius = std::max(radius, 0.f);
  radius = std::min(radius, width * 0.5f);
  radius = std::min(radius, height * 0.5f);

  width = width * 0.5 - radius;
  height = height * 0.5 - radius;
  std::vector<smk::Vertex> v;
  smk::Vertex p0 = {{0.f, 0.f}, {0.f, 0.f}};
  smk::Vertex p1 = {{width + radius, -height}, {0.f, 0.f}};
  smk::Vertex p2 = {{width + radius, height}, {0.f, 0.f}};

  v.push_back(p0);
  v.push_back(p1);
  v.push_back(p2);

  float angle_delta = 2.0 * M_PI / 40.f;  // 0.01f;//radius * 0.01f;

  auto center = glm::vec2(width, radius);
  for (float angle = 0.f; angle < 2.f * M_PI; angle += angle_delta) {
    if (angle > 0.75 * 2.f * M_PI)
      center = glm::vec2(width, -height);
    else if (angle > 0.5 * 2.f * M_PI)
      center = glm::vec2(-width, -height);
    else if (angle > 0.25 * 2.f * M_PI)
      center = glm::vec2(-width, +height);
    else
      center = glm::vec2(+width, +height);

    p1 = p2;
    p2 = {center + radius * glm::vec2(cos(angle), sin(angle)), {0.f, 0.f}};

    v.push_back(p0);
    v.push_back(p1);
    v.push_back(p2);
  }

  p1 = p2;
  p2 = {{width + radius, -height}, {0.f, 0.f}};
  v.push_back(p0);
  v.push_back(p1);
  v.push_back(p2);

  return smk::Shape::FromVertexArray(smk::VertexArray(std::move(v)));
}

}  // namespace smk
