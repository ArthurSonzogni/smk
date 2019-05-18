// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_BLENDMODE_HPP
#define SMK_BLENDMODE_HPP

#include <smk/OpenGL.hpp>

namespace smk {

// out = equation(A * B, C * D);
struct BlendMode {

  // glBlendEquation
  GLenum equation_rgb = GL_FUNC_ADD;
  GLenum equation_alpha = GL_FUNC_ADD;

  // See glBlendFuncSeparate
  GLenum src_rgb = GL_SRC_ALPHA;
  GLenum dst_rgb = GL_ONE_MINUS_SRC_ALPHA;
  GLenum src_alpha = GL_ONE;
  GLenum dst_alpha = GL_ONE;

  // Some predefined blend mode.
  static const BlendMode Replace;    // dst = src
  static const BlendMode Add;        // dst += src
  static const BlendMode Substract;  // dst -= src
  static const BlendMode Multiply;   // dst *= src
  static const BlendMode Alpha;      // dst = src * a + dest * (1 - a)
  static const BlendMode Invert;     // dst = 1 - dst

  bool operator==(const BlendMode&) const;
  bool operator!=(const BlendMode&) const;
};

}  // namespace smk

#endif /* end of include guard: SMK_BLENDMODE_HPP */
