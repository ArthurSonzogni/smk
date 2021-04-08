// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cstdlib>
#include <iostream>
#include <smk/Texture.hpp>
#include <vector>

#include "StbImage.hpp"

namespace smk {
extern bool g_invalidate_textures;

int next_power_of_2(int v) {
  return v;
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

/// @brief Load a texture from a file.
/// @param filename: The file name of the image to be loaded
Texture::Texture(const std::string& filename) : Texture(filename, Option()) {}

/// @brief Load a texture from a file.
/// @param filename The file name of the image to be loaded.
/// @param option Additionnal option (texture wrap, min filter, mag filter, ...)
Texture::Texture(const std::string& filename, const Option& option) {
  FILE* file = fopen(filename.c_str(), "rb");
  if (!file) {
    std::cerr << "File " << filename << " not found" << std::endl;
    return;
  }

  int comp = -1;
  unsigned char* data = stbi_load_from_file(file, &width_, &height_, &comp, 0);
  fclose(file);

  // Canonicalize the image to RGBA(8,8,8,8) and maybe on power_of_2 texture.
  int width_b = next_power_of_2(width_);
  int height_b = next_power_of_2(height_);
  std::vector<uint8_t> transformed(width_b * height_b * 4, 0);
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      for (int c = 0; c < 4; ++c) {
        transformed[c + 4 * (x + width_b * y)] =
            (c == 3 && comp != 4) ? 255 : data[c + comp * (x + width_ * y)];
      }
    }
  }
  Load(transformed.data(), width_b, height_b, option);
  stbi_image_free(data);
}

/// @brief Load a texture from memory (RAM)
/// @param data The memory area to read the image from.
/// @param width the image's with.
/// @param height the image's height.
Texture::Texture(const uint8_t* data, int width, int height)
    : Texture(data, width, height, Option()) {}

/// @brief Load a texture from memory (RAM)
/// @param data The memory area to read the image from.
/// @param width the image's with.
/// @param height the image's height.
/// @param option Additionnal option (texture wrap, min filter, mag filter, ...)
Texture::Texture(const uint8_t* data,
                 int width,
                 int height,
                 const Option& option)
    : Texture() {
  width_ = width;
  height_ = height;
  Load(data, width_, height_, option);
}

void Texture::Load(const uint8_t* data,
                   int width,
                   int height,
                   const Option& option) {
  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, option.internal_format, width, height, 0,
               option.format, option.type, data);
  if (option.generate_mipmap)
    glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, option.min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, option.mag_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, option.wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, option.wrap_t);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
  g_invalidate_textures = true;
}

/// @brief Import an already loaded texture. Useful
/// @param id The OpenGL identifier of the loaded texture.
/// @param width the image's with.
/// @param height the image's height.
Texture::Texture(GLuint id, int width, int height)
    : id_(id), width_(width), height_(height) {}

/// @brief The null texture.
Texture::Texture() = default;
Texture::~Texture() {
  int* ref_count = ref_count_;
  id_ = 0;
  width_ = -1;
  height_ = -1;

  if (!id_)
    return;

  if (ref_count) {
    --(*ref_count);
    if (*ref_count)
      return;
    delete ref_count;
    ref_count = nullptr;
  }

  glDeleteTextures(1, &id_);
}

Texture::Texture(Texture&& other) noexcept {
  operator=(std::move(other));
}

Texture::Texture(const Texture& other) {
  operator=(other);
}

void Texture::operator=(Texture&& other) noexcept {
  this->~Texture();
  std::swap(id_, other.id_);
  std::swap(width_, other.width_);
  std::swap(height_, other.height_);
  std::swap(ref_count_, other.ref_count_);
}

Texture& Texture::operator=(const Texture& other) {
  this->~Texture();
  id_ = other.id_;
  width_ = other.width_;
  height_ = other.height_;

  if (!other.id_)
    return *this;

  if (!other.ref_count_)
    other.ref_count_ = new int(1);

  ref_count_ = other.ref_count_;
  (*ref_count_)++;
  return *this;
}

void Texture::Bind(GLuint activetexture) const {
  glActiveTexture(activetexture);
  glBindTexture(GL_TEXTURE_2D, id_);
}

bool Texture::operator==(const Texture& other) {
  return id_ == other.id_;
}

bool Texture::operator!=(const Texture& other) {
  return id_ != other.id_;
}

/// @brief Access the width of the texture
/// @return The texture's width in pixel
int Texture::width() const {
  return width_;
}

/// @brief Access the height of the texture
/// @return The texture's height in pixel
int Texture::height() const {
  return height_;
}

/// @brief Access the ID of the texture
/// @return The texture's ID.
GLuint Texture::id() const {
  return id_;
}

}  // namespace smk
