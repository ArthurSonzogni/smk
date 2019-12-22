// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/Window.hpp>

#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include <smk/Color.hpp>
#include <smk/Drawable.hpp>
#include <smk/Input.hpp>
#include <smk/OpenGL.hpp>
#include <smk/View.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <cmath>
#endif

namespace smk {

Window::Window() {}
Window::Window(int width, int height, const std::string& title) {
  width_ = width;
  height_ = height;

  // initialize the GLFW library
  if (!glfwInit()) {
    throw std::runtime_error("Couldn't init GLFW");
  }

  // setting the opengl version
#ifdef __EMSCRIPTEN__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  // create the window_
  window_ = glfwCreateWindow(width_, height_, title.c_str(), NULL, NULL);
  if (!window_) {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window_");
  }

  glfwMakeContextCurrent(window_);

#ifndef __EMSCRIPTEN__
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error(std::string("Could initialize GLEW, error = ") +
                             (const char*)glewGetErrorString(err));
  }
#endif

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported " << version << std::endl;

  // Alpha transparency.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  InitRenderTarget();
}

Window::Window(Window&& window) {
  operator=(std::move(window));
}

void Window::operator=(Window&& other) {
  RenderTarget::operator=(std::move(other));
  std::swap(window_, other.window_);
  std::swap(time_, other.time_);
  std::swap(time_last_sleep_, other.time_last_sleep_);
  std::swap(input_, other.input_);
}

void Window::PoolEvents() {
  glfwPollEvents();
  input_.Update(window_);
}

void Window::Display() {
  // Swap Front and Back buffers (double buffering)
  glfwSwapBuffers(window_);

  // Detect window_ related changes
  UpdateDimensions();

  time_ = glfwGetTime();
}

Window::~Window() {
  // glfwTerminate(); // Needed? What about multiple windows?
}

void Window::UpdateDimensions() {
  int width = width_;
  int height = height_;
#ifdef __EMSCRIPTEN__
  emscripten_get_canvas_element_size("canvas", &width_, &height_);
#else
  glfwGetWindowSize(window_, &width_, &height_);
#endif

  if (width != width_ || height != height_) {
    glViewport(0, 0, width_, height_);
    SetView(view_);
  }
}

void Window::LimitFrameRate(float fps) {
  const float delta = glfwGetTime() - time_last_sleep_;
  const float target = 1.f / fps;
  float sleep_duration = target - delta;
  sleep_duration = std::max(0.f, std::min(target, sleep_duration));
  std::this_thread::sleep_for(
      std::chrono::microseconds(int(sleep_duration * 1'000'000)));
  time_last_sleep_ = glfwGetTime();
}

} // namespace smk