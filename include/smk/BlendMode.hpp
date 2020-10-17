// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_BLENDMODE_HPP
#define SMK_BLENDMODE_HPP

#include <smk/OpenGL.hpp>

namespace smk {

/// Blending modes for drawing.
///
/// When drawing something into a smk::RenderTarget, the smk::BlendMode
/// represents how the colors are mixed with the colors already in the color
/// buffer.
///
/// ## Commonly used BlendMode
///
/// SMK provides 6 predefined common BlendMode:
/// ~~~cpp
/// smk::BlendMode::Replace;   // dst = src
/// smk::BlendMode::Add;       // dst += src
/// smk::BlendMode::Subtract; // dst -= src
/// smk::BlendMode::Multiply;  // dst *= src
/// smk::BlendMode::Alpha;     // dst = src * a + dest * (1 - a)
/// smk::BlendMode::Invert;    // dst = 1 - dst
/// ~~~
///
/// ### Example:
///
/// ~~~cpp
/// sprite.SetBlendMode(smk::BlendMode::Add);
/// ~~~
///
/// ## Custom BlendMode:
///
/// This struct wrap all the parameters used by:
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBlendEquation.xhtml
///
/// They define how the destination "dst" pixel is computed, knowing the source
/// "src" pixel value.
///
/// ~~~cpp
/// dst.rgb = equation_rgb(src_rgb * src.rgb, dst_rgb / src.rgb)
/// dst.alpha = equation_alpha(src_alpha * src.alpha, dst_alpha / src.alpha)
/// ~~~
///
/// ### Example
///
/// ~~~cpp
/// smk::BlendMode blend_mode = {
///     GL_FUNC_ADD, // equation_rgb
///     GL_FUNC_ADD, // equation_alpha
///     GL_ONE,      // src_rgb factor
///     GL_ZERO,     // dst_rgb factor
///     GL_ONE,      // src_alpha factor
///     GL_ZERO,     // dst_alpha factor
/// };
/// sprite.SetBlendMode(blend_mode);
/// ~~~
struct BlendMode {
  // Preset of BlendMode:
  static const BlendMode Replace;  // dst = src
  static const BlendMode Add;      // dst += src
  static const BlendMode Subtract; // dst -= src
  static const BlendMode Multiply; // dst *= src
  static const BlendMode Alpha;    // dst = src * a + dest * (1 - a)
  static const BlendMode Invert;   // dst = 1 - dst

  // glBlendEquation
  GLenum equation_rgb = GL_FUNC_ADD;
  GLenum equation_alpha = GL_FUNC_ADD;

  // See glBlendFuncSeparate
  GLenum src_rgb = GL_SRC_ALPHA;
  GLenum dst_rgb = GL_ONE_MINUS_SRC_ALPHA;
  GLenum src_alpha = GL_ONE;
  GLenum dst_alpha = GL_ONE;

  bool operator==(const BlendMode&) const;
  bool operator!=(const BlendMode&) const;
};

}  // namespace smk

#endif /* end of include guard: SMK_BLENDMODE_HPP */
