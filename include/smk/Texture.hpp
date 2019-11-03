// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_TEXTURE_HPP
#define SMK_TEXTURE_HPP

#include <smk/OpenGL.hpp>
#include <string>

namespace smk {

struct Texture {
 public:
  struct Option {
    GLenum min_filter = GL_LINEAR_MIPMAP_LINEAR;
    GLenum mag_filter = GL_LINEAR;
    GLenum wrap_s = GL_CLAMP_TO_EDGE;
    GLenum wrap_t = GL_CLAMP_TO_EDGE;
  };

  Texture();  // empty texture.
  Texture(const std::string& filename);
  Texture(const std::string& filename, Option option);

  ~Texture();

  void Bind(GLuint active_texture = GL_TEXTURE0) const;

  GLuint id = 0;
  int width = -1;
  int height = -1;

  operator bool() const { return id != 0; }

  // --- Move only resource ----------------------------------------------------
  Texture(Texture&&);
  Texture(const Texture&) = delete;
  void operator=(Texture&&);
  void operator=(const Texture&) = delete;
  // ---------------------------------------------------------------------------
};

} // namespace smk

#endif  // SMK_TEXTURE_HPP
