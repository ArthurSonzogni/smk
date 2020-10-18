// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/BlendMode.hpp>

namespace smk {

/// @brief destination = source.
const BlendMode BlendMode::Replace = {
    GL_FUNC_ADD, GL_FUNC_ADD, GL_ONE, GL_ZERO, GL_ONE, GL_ZERO,
};

/// @brief destination += source.
const BlendMode BlendMode::Add = {
    GL_FUNC_ADD, GL_FUNC_ADD, GL_SRC_ALPHA, GL_ONE, GL_ONE, GL_ONE,
};

/// @brief destination -= source.
const BlendMode BlendMode::Subtract = {
    GL_FUNC_REVERSE_SUBTRACT,
    GL_FUNC_REVERSE_SUBTRACT,
    GL_ONE,
    GL_ONE,
    GL_ONE,
    GL_ONE,
};

/// @brief destination = source * source.a + destination * (1 - souce.a)
const BlendMode BlendMode::Alpha = {
    GL_FUNC_ADD,  GL_FUNC_ADD,
    GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
    GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
};

/// @brief destination *= source
const BlendMode BlendMode::Multiply = {
    GL_FUNC_ADD, GL_FUNC_ADD, GL_DST_COLOR, GL_ZERO, GL_DST_ALPHA, GL_ZERO,
};

/// @brief destination = 1 - destination
const BlendMode BlendMode::Invert = {
    GL_FUNC_ADD,
    GL_FUNC_ADD,
    GL_ONE_MINUS_DST_COLOR,
    GL_ZERO,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_ZERO,
};

bool BlendMode::operator==(const BlendMode& o) const {
  return equation_rgb == o.equation_rgb &&      //
         equation_alpha == o.equation_alpha &&  //
         src_rgb == o.src_rgb &&                //
         dst_rgb == o.dst_rgb &&                //
         src_alpha == o.src_alpha &&            //
         dst_alpha == o.dst_alpha;              //
}

bool BlendMode::operator!=(const BlendMode& o) const {
  return !operator==(o);
}

}  // namespace smk
