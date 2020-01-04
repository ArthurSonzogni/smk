// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cstdlib>
#include <iostream>
#include <smk/Texture.hpp>
#include <vector>

#include "StbImage.hpp"

namespace smk {
extern bool invalidate_texture;

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

Texture::Texture(const std::string& filename) : Texture(filename, Option()) {}
Texture::Texture(const std::string& filename, Option option) {
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

Texture::Texture(const uint8_t* data, int width, int height)
    : Texture(data, width, height, Option()) {}

Texture::Texture(const uint8_t* data, int width, int height, Option option)
    : Texture() {
  width_ = width;
  height_ = height;
  Load(data, width_, height_, option);
}

void Texture::Load(const uint8_t* data, int width, int height, Option option) {
  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, option.min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, option.mag_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, option.wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, option.wrap_t);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
  invalidate_texture = true;
}

Texture::Texture(GLuint id, int width, int height)
    : id_(id), width_(width), height_(height) {}

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

Texture::Texture(Texture&& other) {
  operator=(std::move(other));
}

Texture::Texture(const Texture& other) {
  operator=(other);
}

void Texture::operator=(Texture&& other) {
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

}  // namespace smk
