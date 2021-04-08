// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Color.hpp>
#include <smk/Drawable.hpp>
#include <smk/Framebuffer.hpp>
#include <smk/RenderState.hpp>

namespace smk {

/// @brief Construct a Framebuffer of a given dimensions.
/// @param width The width of the drawing surface.
/// @param height The width of the drawing surface.
Framebuffer::Framebuffer(int width, int height) {
  Texture::Option option;
  option.internal_format = GL_RGB;
  option.format = GL_RGB;
  option.type = GL_UNSIGNED_BYTE;
  option.generate_mipmap = false;
  option.min_filter = GL_LINEAR;
  option.mag_filter = GL_LINEAR;
  color_textures_.push_back(smk::Texture(nullptr, width, height, option));

  Init();
}

/// @brief Construct a Framebuffer from a list of color textures. Those textures
/// must be constructed with not mipmap. See Texture::Option::generate_mipma^
// /and Texture::Option::min_filter.
/// @param width The width of the drawing surface.
/// @param height The width of the drawing surface.
Framebuffer::Framebuffer(std::vector<Texture> color_textures)
    : color_textures_(std::move(color_textures)) {
  Init();
}

void Framebuffer::Init() {
  width_ = color_texture().width();
  height_ = color_texture().height();

  // The frame buffer.
  glGenFramebuffers(1, &frame_buffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);

  // Attach the textures to the framebuffer.
  for (size_t i = 0; i < color_textures_.size(); ++i) {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                           GL_TEXTURE_2D, color_textures_[i].id(), 0);
  }

  // The render buffer.
  glGenRenderbuffers(1, &render_buffer_);
  glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  // Attach it to the framebuffer.
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, render_buffer_);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!"
              << std::endl;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  InitRenderTarget();
}

Framebuffer::~Framebuffer() {
  if (frame_buffer_) {
    glDeleteFramebuffers(1, &frame_buffer_);
    frame_buffer_ = 0;
  }

  if (render_buffer_) {
    glDeleteRenderbuffers(1, &render_buffer_);
    render_buffer_ = 0;
  }
}

Framebuffer::Framebuffer(Framebuffer&& other) noexcept {
  this->operator=(std::move(other));
}

void Framebuffer::operator=(Framebuffer&& other) noexcept {
  RenderTarget::operator=(std::move(other));
  std::swap(color_textures_, other.color_textures_);
  std::swap(render_buffer_, other.render_buffer_);
}

smk::Texture& Framebuffer::color_texture() {
  return color_textures_[0];
}

}  // namespace smk
