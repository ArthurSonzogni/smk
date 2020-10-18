// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <algorithm>
#include <chrono>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <smk/Color.hpp>
#include <smk/Drawable.hpp>
#include <smk/Input.hpp>
#include <smk/InputImpl.hpp>
#include <smk/OpenGL.hpp>
#include <smk/View.hpp>
#include <smk/Window.hpp>
#include <thread>
#include <vector>

#ifdef __EMSCRIPTEN__
  #include <emscripten.h>
  #include <emscripten/html5.h>
#endif

namespace smk {

bool g_khr_parallel_shader = false;

namespace {

int g_next_id = 0;
std::map<int, Window*> window_by_id;
std::map<GLFWwindow*, Window*> window_by_glfw_window;

void GLFWScrollCallback(GLFWwindow* glfw_window,
                        double xoffset,
                        double yoffset) {
  Window* window = window_by_glfw_window[glfw_window];
  if (!window)
    return;

  static_cast<InputImpl*>(&(window->input()))
      ->OnScrollEvent({xoffset, yoffset});
}

void GLFWErrorCallback(int error, const char* description) {
  std::cerr << "GFLW error n°" << error << std::endl;
  std::cerr << "~~~" << std::endl;
  std::cerr << description << std::endl;
  std::cerr << "~~~" << std::endl;
  fprintf(stderr, "Error: %s\n", description);
}

#ifdef __EMSCRIPTEN__

EM_BOOL OnTouchEvent(int eventType,
                     const EmscriptenTouchEvent* keyEvent,
                     void* userData) {
  int g_next_id = (int)(userData);
  Window* window = window_by_id[g_next_id];
  if (!window)
    return false;
  static_cast<InputImpl*>(&(window->input()))
      ->OnTouchEvent(eventType, keyEvent);
  return true;
}

std::function<void(void)> main_loop;
void MainLoop() {
  return main_loop();
}

EM_JS(void, MakeCanvasSelectable, (int window_id), {
  if (!Module)
    return;

  if (!Module['canvas'])
    return;

  Module['canvas'].setAttribute("smk", window_id);
});

#endif

#if !defined NDEBUG && !defined __EMSCRIPTEN__ && __linux__
void OpenGLDebugMessageCallback(GLenum /*source*/,
                                GLenum type,
                                GLuint /*g_next_id*/,
                                GLenum /*severity*/,
                                GLsizei length,
                                const GLchar* message,
                                const void* /*userParam*/) {
  if (type == GL_DEBUG_TYPE_OTHER)
    return;
  std::cerr << "SMK > OpenGL error: " << std::string(message, length)
            << std::endl;
}
#endif

void GLFWCharCallback(GLFWwindow* glfw_window, unsigned int codepoint) {
  Window* window = window_by_glfw_window[glfw_window];
  if (!window)
    return;
  static_cast<InputImpl*>(&(window->input()))
      ->OnCharacterTyped((wchar_t)codepoint);
}

}  // namespace

/// @brief A null window.
Window::Window() {
  id_ = ++g_next_id;
  window_by_id[id_] = this;
}

/// @brief The window construtor.
/// @param width The desired width of the window.
/// @param height The desired height of the window.
/// @param title The window's title.
Window::Window(int width, int height, const std::string& title) {
  input_ = std::make_unique<InputImpl>();
  id_ = ++g_next_id;
  window_by_id[id_] = this;
  width_ = width;
  height_ = height;

  glfwSetErrorCallback(GLFWErrorCallback);
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
  window_by_glfw_window[window_] = this;

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

#if !defined NDEBUG && !defined __EMSCRIPTEN__ && __linux__
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(OpenGLDebugMessageCallback, 0);
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

#ifndef __EMSCRIPTEN__
  if (GLEW_KHR_parallel_shader_compile) {
    glMaxShaderCompilerThreadsKHR(4);
    g_khr_parallel_shader = true;
  }
#else
  g_khr_parallel_shader = emscripten_webgl_enable_extension(
      emscripten_webgl_get_current_context(), "KHR_parallel_shader_compile");

  MakeCanvasSelectable(id_);

  module_canvas_selector_ = "[smk='" + std::to_string(id_) + "']";

  emscripten_set_touchstart_callback(module_canvas_selector_.c_str(),
                                     (void*)id_, true, OnTouchEvent);
  emscripten_set_touchend_callback(module_canvas_selector_.c_str(), (void*)id_,
                                   true, OnTouchEvent);
  emscripten_set_touchmove_callback(module_canvas_selector_.c_str(), (void*)id_,
                                    true, OnTouchEvent);
  emscripten_set_touchcancel_callback(module_canvas_selector_.c_str(),
                                      (void*)id_, true, OnTouchEvent);
#endif
  glfwSetScrollCallback(window_, GLFWScrollCallback);
  glfwSetCharCallback(window_, GLFWCharCallback);
}

Window::Window(Window&& window) noexcept {
  operator=(std::move(window));
}

void Window::operator=(Window&& other) noexcept {
  RenderTarget::operator=(std::move(other));
  std::swap(window_, other.window_);
  std::swap(time_, other.time_);
  std::swap(time_last_sleep_, other.time_last_sleep_);
  std::swap(input_, other.input_);
  std::swap(id_, other.id_);
  std::swap(module_canvas_selector_, other.module_canvas_selector_);
  window_by_id[id_] = this;
  window_by_glfw_window[window_] = this;
}

/// @brief Handle all the new input events. This update the input() object.
void Window::PoolEvents() {
  glfwPollEvents();
  input_->Update(window_);
}

/// @brief Present what has been draw to the screen.
void Window::Display() {
  // Swap Front and Back buffers (double buffering)
  glfwSwapBuffers(window_);

  // Detect window_ related changes
  UpdateDimensions();

  time_ = glfwGetTime();
}

Window::~Window() {
  window_by_id.erase(id_);
  // glfwTerminate(); // Needed? What about multiple windows?
}

/// The window handle.
GLFWwindow* Window::window() const {
  return window_;
}

/// The last time Window::PoolEvent() was called.
float Window::time() const {
  return time_;
}

/// Return an object for querying the input state.
Input& Window::input() {
  return *(input_.get());
}

/// @brief Helper function. Execute the main loop of the application.
/// On web based application: registers the loop in 'requestAnimationFrame'.
/// On desktop based applications: This is a simple 'while' loop. The loop stops
/// when the user presses the 'escape' button or when the |loop| function
/// returns 'false'.
/// @param loop The function to be called for each new frame.
void Window::ExecuteMainLoopUntil(std::function<bool(void)> loop) {
#ifdef __EMSCRIPTEN__
  main_loop = [my_loop = loop] { (void)my_loop(); };
  emscripten_set_main_loop(&MainLoop, 0, 1);
#else
  while (loop())
    LimitFrameRate(60.0f);
#endif
}

/// @brief Helper function. Execute the main loop of the application.
/// On web based application: registers the loop in 'requestAnimationFrame'.
/// On desktop based applications: This is a simple 'while' loop. The loop stops
/// when the user presses the 'escape' button or when the |loop| function
/// returns 'false'.
/// @param loop The function to be called for each new frame.
void Window::ExecuteMainLoop(std::function<void(void)> loop) {
#ifdef __EMSCRIPTEN__
  main_loop = loop;
  emscripten_set_main_loop(&MainLoop, 0, 1);
#else
  while (!input().IsKeyPressed(GLFW_KEY_ESCAPE) && !ShouldClose()) {
    loop();
    LimitFrameRate(60.0f);
  };
#endif
}

void Window::UpdateDimensions() {
  int width = width_;
  int height = height_;
#ifdef __EMSCRIPTEN__
  emscripten_get_canvas_element_size(module_canvas_selector_.c_str(), &width_,
                                     &height_);
#else
  glfwGetWindowSize(window_, &width_, &height_);
#endif

  if (width != width_ || height != height_) {
    glViewport(0, 0, width_, height_);
    SetView(view_);
  }
}

/// If needed, insert pause in the execution to maintain a given framerate.
/// @param fps the desired frame rate.
void Window::LimitFrameRate(float fps) {
  const float delta = glfwGetTime() - time_last_sleep_;
  const float target = 1.f / fps;
  float sleep_duration = target - delta;
  sleep_duration = std::min(target, sleep_duration);
  if (sleep_duration > 0.f) {
    std::this_thread::sleep_for(
        std::chrono::microseconds(int(sleep_duration * 1'000'000)));
  }
  time_last_sleep_ = glfwGetTime();
}

/// Returns true when the user wants to close the window.
bool Window::ShouldClose() {
  return glfwWindowShouldClose(window_);
}

}  // namespace smk
