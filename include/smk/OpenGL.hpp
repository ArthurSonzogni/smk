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

  #ifndef GLEW_KHR_parallel_shader_compile
    #define GLEW_KHR_parallel_shader_compile 1
    #define GL_MAX_SHADER_COMPILER_THREADS_KHR 0x91B0
    #define GL_COMPLETION_STATUS_KHR 0x91B1
typedef void(GL_APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC)(GLuint count);
  #endif /* GL_KHR_parallel_shader_compile */

#else
  #include <GL/glew.h>
  #include <GLFW/glfw3.h>
#endif

#endif /* end of include guard: SMK_OPENGL_HPP */
