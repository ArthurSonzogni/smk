// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cstdlib>
#include <iostream>
#include <smk/Texture.hpp>
#include <vector>

#include "StbImage.hpp"

namespace smk {

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
  unsigned char* data = stbi_load_from_file(file, &width, &height, &comp, 0);
  fclose(file);

  // Canonicalize the image to RGBA(8,8,8,8) and maybe on power_of_2 texture.
  int width_b = next_power_of_2(width);
  int height_b = next_power_of_2(height);
  std::vector<unsigned char> transformed(width_b * height_b * 4, 0);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int c = 0; c < 4; ++c) {
        transformed[c + 4 * (x + width_b * y)] =
            (c == 3 && comp != 4) ? 255 : data[c + comp * (x + width * y)];
      }
    }
  }

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_b, height_b, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, transformed.data());
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, option.min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, option.mag_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, option.wrap_s);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, option.wrap_t);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);
  stbi_image_free(data);
}

Texture::Texture() = default;
Texture::~Texture() {
  if (id)
    glDeleteTextures(1, &id);
  id = 0;
  width = -1;
  height = -1;
}

Texture::Texture(Texture&& other)
    : id(other.id), width(other.width), height(other.height) {
  other.id = 0;
  other.width = -1;
  other.height = -1;
}

void Texture::operator=(Texture&& other) {
  this->~Texture();
  std::swap(id, other.id);
  std::swap(width, other.width);
  std::swap(height, other.height);
}

void Texture::Bind(GLuint activetexture) const {
  glActiveTexture(activetexture);
  glBindTexture(GL_TEXTURE_2D, id);
}

}  // namespace smk
