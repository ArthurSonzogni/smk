// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_OPENGL_HPP
#define SMK_OPENGL_HPP

#ifdef __EMSCRIPTEN__
  #include <GLES3/gl3.h>
  #include <emscripten/emscripten.h>
  #define GLFW_INCLUDE_ES3
  #include <GLFW/glfw3.h>
#else
  #include <GL/glew.h>
  #include <GLFW/glfw3.h>
#endif

#endif /* end of include guard: SMK_OPENGL_HPP */
