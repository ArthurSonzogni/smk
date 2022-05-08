// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_TEXTURE_HPP
#define SMK_TEXTURE_HPP

#include <smk/OpenGL.hpp>
#include <string>

namespace smk {

/// A texture loaded from a file into the GPU. This class support the move and
/// copy operators. Its underlying GPU texture is refcounted and released when
/// then last smk::Texture is deleted.
///
/// Example:
/// --------
///
/// ~~~cpp
/// auto texture = smk::Texture("./ball.png");
/// ~~~
///
/// Supported image encoding:
/// -------------------------
///
/// The SMK library uses the stb_image. So it supports the same image types:
/// - JPEG baseline & progressive (12 bpc/arithmetic not supported, same as
/// stock IJG lib)
/// - PNG 1/2/4/8/16-bit-per-channel
/// - TGA
/// - BMP non-1bpp, non-RLE
/// - PSD (composited view only, no extra channels, 8/16 bit-per-channel)
/// - GIF
/// - HDR (radiance rgbE format)
/// - PIC (Softimage PIC)
/// - PNM (PPM and PGM binary only)
struct Texture {
 public:
  struct Option {
    GLint min_filter = GL_LINEAR_MIPMAP_LINEAR;
    GLint mag_filter = GL_LINEAR;
    GLint wrap_s = GL_CLAMP_TO_EDGE;
    GLint wrap_t = GL_CLAMP_TO_EDGE;
    GLint internal_format = GL_RGBA;
    GLint format = GL_RGBA;
    GLint type = GL_UNSIGNED_BYTE;
    bool generate_mipmap = true;
  };

  Texture();  // empty texture.
  Texture(const std::string& filename);
  Texture(const std::string& filename, const Option& option);
  Texture(const uint8_t* data, int width, int height);
  Texture(const uint8_t* data, int width, int height, const Option& option);
  Texture(GLuint id, int width, int height);
  ~Texture();

  void Bind(GLuint active_texture = GL_TEXTURE0) const;

  int width() const;
  int height() const;
  GLuint id() const;

  operator bool() const { return id_ != 0; }

  // --- Copyable Movable resource ---------------------------------------------
  Texture(Texture&&) noexcept;
  Texture(const Texture&);
  Texture& operator=(Texture&&) noexcept;
  Texture& operator=(const Texture&);
  //----------------------------------------------------------------------------
  bool operator==(const Texture& other) const;
  bool operator!=(const Texture& other) const;

 private:
  void Release();
  void Load(const uint8_t* data, int width, int height, const Option& option);
  GLuint id_ = 0;
  int width_ = 0;
  int height_ = 0;

  // Used to support copy. Nullptr as long as this class is not copied.
  // Otherwise an integer counting how many instances shares this resource.
  mutable int* ref_count_ = nullptr;
};

}  // namespace smk

#endif  // SMK_TEXTURE_HPP
