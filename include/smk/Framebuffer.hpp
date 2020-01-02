// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_FRAMEBUFFER_HPP
#define SMK_FRAMEBUFFER_HPP

#include <iostream>
#include <smk/OpenGL.hpp>
#include <smk/RenderTarget.hpp>
#include <smk/Texture.hpp>

namespace smk {

class Framebuffer : public RenderTarget {
 public:
  Framebuffer(int width, int height);
  Framebuffer(Framebuffer&&);
  Framebuffer(const Framebuffer&) = delete;
  ~Framebuffer();
  void operator=(Framebuffer&&);
  void operator=(const Framebuffer&) = delete;

  smk::Texture color_texture;

 private:
  GLuint render_buffer_ = 0;
};

}  // namespace smk

#endif /* end of include guard: SMK_FRAMEBUFFER_HPP */
