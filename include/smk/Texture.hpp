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
  Texture(const uint8_t* data, int width, int height);
  Texture(const uint8_t* data, int width, int height, Option option);
  Texture(GLuint id, int width, int height);
  ~Texture();

  void Bind(GLuint active_texture = GL_TEXTURE0) const;

  int width() const { return width_; }
  int height() const { return height_; }
  GLuint id() const { return id_; }

  operator bool() const { return id_ != 0; }

  // --- Copyable Movable resource ---------------------------------------------
  Texture(Texture&&);
  Texture(const Texture&);
  void operator=(Texture&&);
  Texture& operator=(const Texture&);

 private:
  void Load(const uint8_t* data, int width, int height, Option option);
  GLuint id_ = 0;
  int width_ = -1;
  int height_ = -1;

  // Used to support copy. Nullptr as long as this class is not copied.
  // Otherwise an integer counting how many instances shares this resource.
  mutable int* ref_count_ = nullptr;
};

}  // namespace smk

#endif  // SMK_TEXTURE_HPP
