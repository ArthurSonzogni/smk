// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <cstdlib>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <smk/Shader.hpp>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <vector>

namespace smk {

extern bool g_khr_parallel_shader;

using namespace glm;

const std::string kShaderHeader =
#ifdef __EMSCRIPTEN__
    "#version 300 es\n"
    "precision mediump float;\n"
    "precision mediump int;\n"
    "precision mediump sampler2DArray;\n";
#else
    "#version 330\n";
#endif

// static
/// @brief Load a shader from a file.
/// @param filename The text filename where the shader is written.
/// @param type
///   Either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER. It can also be
///   any other shader type defined by OpenGL.
///   See
///   https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
//
/// @see Shader::FromString
/// @see Shader::FromFile
Shader Shader::FromFile(const std::string& filename, GLenum type) {
  std::ifstream file(filename);
  return Shader::FromString(std::string(std::istreambuf_iterator<char>(file),
                                        std::istreambuf_iterator<char>()),
                            type);
}

// static
/// @brief Load a shader from a std::string.
/// @param content The string representing the shader.
/// @param type
///   Either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER. It can also be
///   any other shader type defined by OpenGL.
///   See
///   https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
//
/// @see Shader::FromString
/// @see Shader::FromFile
Shader Shader::FromString(const std::string& content, GLenum type) {
  std::vector<char> buffer;
  for (const auto& c : kShaderHeader)
    buffer.push_back(c);
  for (const auto& c : content)
    buffer.push_back(c);
  buffer.push_back('\0');
  return Shader(std::move(buffer), type);
}

/// @brief The GPU shader id.
/// @return The OpenGL shader id. If the Shader is invalid, returns zero.
GLuint Shader::id() const {
  return id_;
}

Shader::Shader() = default;
Shader::Shader(const std::vector<char>& content, GLenum type) {
  // creation
  id_ = glCreateShader(type);
  if (id_ == 0) {
    std::cerr << "[Error] Impossible to create a new Shader" << std::endl;
    throw std::runtime_error("[Error] Impossible to create a new Shader");
  }

  // code source assignation
  const char* shaderText(&content[0]);
  glShaderSource(id_, 1, (const GLchar**)&shaderText, NULL);

  // compilation
  glCompileShader(id_);
}

/// @brief Check the status of a Shader.
/// Linking shader is an asynchronous process. Using the shader can causes the
/// CPU to wait until its completion. If you need to do some work before the
/// completion, you can use this function and use the Shader only after it
/// becomes ready.
bool Shader::IsReady() {
  if (g_khr_parallel_shader) {
    GLint completion_status;
    glGetShaderiv(id_, GL_COMPLETION_STATUS_KHR, &completion_status);
    return completion_status == GL_TRUE;
  }

  std::cerr << "Used bad path" << std::endl;
  return true;
}

/// @brief Wait until the Shader to be ready.
/// @return True if it suceeded, false otherwise.
bool Shader::CompileStatus() {
  GLint compile_status;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == GL_TRUE)
    return true;

  GLsizei logsize = 0;
  glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &logsize);

  char* log = new char[logsize + 1];
  glGetShaderInfoLog(id_, logsize, &logsize, log);

  std::cout << "[Error] compilation error: " << std::endl;
  std::cout << log << std::endl;

  return false;
}

Shader::~Shader() {
  Release();
}

Shader::Shader(const Shader& other) noexcept {
  this->operator=(other);
}

Shader::Shader(Shader&& other) noexcept {
  this->operator=(std::move(other));
}

Shader& Shader::operator=(const Shader& other) noexcept {
  Release();
  if (!other.id_)
    return *this;

  if (!other.ref_count_)
    other.ref_count_ = new int(1);

  id_ = other.id_;
  ref_count_ = other.ref_count_;

  (*ref_count_)++;
  return *this;
}

Shader& Shader::operator=(Shader&& other) noexcept {
  std::swap(id_, other.id_);
  std::swap(ref_count_, other.ref_count_);
  return *this;
}

void Shader::Release() {
  // Nothing to do for the null Shader.
  if (!id_)
    return;

  // Transfert state to local:
  GLuint id = 0;
  int* ref_count = nullptr;
  std::swap(id_, id);
  std::swap(ref_count_, ref_count);

  // Early return without releasing the resource if it is still hold by copy of
  // this class.
  if (ref_count) {
    --(*ref_count);
    if (*ref_count)
      return;
    delete ref_count;
    ref_count = nullptr;
  }

  // Release the OpenGL objects.
  glDeleteShader(id);
}

struct ShaderProgram::Impl {
  std::map<std::string, GLint> uniforms;
  GLuint id = 0;

  ~Impl() {
    if (!id)
      return;
    glDeleteProgram(id);
    id = 0;
  }
};

/// @brief The constructor. The ShaderProgram is initially invalid. You need to
/// call @ref AddShader and @ref Link before being able to use it.
ShaderProgram::ShaderProgram() : impl_(new Impl()) {}

/// @brief Add a Shader to the program list. This must called multiple time for
/// each shader components before calling @ref Link.
/// @param shader The Shader to be added to the program list.
void ShaderProgram::AddShader(const Shader& shader) {
  if (!impl_->id) {
    impl_->id = glCreateProgram();
    if (!impl_->id)
      std::cerr << "[Error] Impossible to create a new Shader" << std::endl;
  }

  glAttachShader(id(), shader.id());
}

/// @brief Add a Shader to the program list.
void ShaderProgram::Link() {
  glLinkProgram(id());
}

// Linking shader is an asynchronous process. Using the shader can causes the
// CPU to wait until its completion. If you need to do some work before the
// completion, you can use this function and use the Shader only after it
// becomes ready.
bool ShaderProgram::IsReady() {
  if (g_khr_parallel_shader) {
    GLint completion_status;
    std::cerr << GL_COMPLETION_STATUS_KHR << std::endl;
    std::cerr << id() << std::endl;
    glGetProgramiv(id(), GL_COMPLETION_STATUS_KHR, &completion_status);
    return completion_status == GL_TRUE;
  }

  return true;
}

bool ShaderProgram::LinkStatus() {
  GLint result;
  glGetProgramiv(id(), GL_LINK_STATUS, &result);
  if (result == GL_TRUE)
    return true;

  std::cout << "[Error] linkage error" << std::endl;

  GLsizei logsize = 0;
  glGetProgramiv(id(), GL_INFO_LOG_LENGTH, &logsize);

  char* log = new char[logsize];
  glGetProgramInfoLog(id(), logsize, &logsize, log);

  std::cout << log << std::endl;
  return false;
}

/// @brief Return the uniform ID.
/// @param name The uniform name in the Shader.
/// @return The GPU uniform ID. Return 0 and display an error if not found.
GLint ShaderProgram::Uniform(const std::string& name) {
  auto it = impl_->uniforms.find(name);
  if (it == impl_->uniforms.end()) {
    // impl_->uniforms that is not referenced
    GLint r = glGetUniformLocation(id(), name.c_str());

    if (r == GL_INVALID_OPERATION || r < 0) {
      std::cerr << "[Error] Uniform " << name << " doesn't exist in program"
                << std::endl;
    }
    // add it anyways
    impl_->uniforms[name] = r;

    return r;
  } else
    return it->second;
}

GLint ShaderProgram::operator[](const std::string& name) {
  return Uniform(name);
}

/// @brief Return the GPU attribute id.
/// @param name The attribute name in the Shader.
/// @return The GPU attribute ID. Return 0 and display an error if not found.
GLint ShaderProgram::Attribute(const std::string& name) {
  GLint attrib = glGetAttribLocation(id(), name.c_str());
  if (attrib == GL_INVALID_OPERATION || attrib < 0)
    std::cerr << "[Error] Attribute " << name << " doesn't exist in program"
              << std::endl;

  return attrib;
}

/// @brief
///   Set an OpenGL attribute properties.
/// @param name
///   Attribute name in the Shader.
/// @param size
///   Specify the number of component per object. One of {1,2,3,4}.
/// @param stride
///   Specify the byte offset in between consecutive attribute of
///   the same kind.
/// @param offset
///   Offset of the attribute in the struct.
/// @param type
///   The type of data. For instance GL_FLOAT.
/// @return
///   The GPU attribute ID. Return 0 and display an error if not found.
///
/// @see glVertexAttribPointer
void ShaderProgram::SetAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset,
                                 GLboolean normalize,
                                 GLenum type) {
  GLint loc = Attribute(name);
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, size, type, normalize, stride,
                        reinterpret_cast<void*>(offset));
}

/// @brief Set an OpenGL attribute properties, assuming data are float.
/// @see SetAttribute.
void ShaderProgram::SetAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset,
                                 GLboolean normalize) {
  SetAttribute(name, size, stride, offset, normalize, GL_FLOAT);
}

/// @brief Set an OpenGL attribute properties, assuming data are float.
/// @see SetAttribute.
void ShaderProgram::SetAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset,
                                 GLenum type) {
  SetAttribute(name, size, stride, offset, false, type);
}

/// @brief Set an OpenGL attribute properties, assuming data are float.
/// @see SetAttribute.
void ShaderProgram::SetAttribute(const std::string& name,
                                 GLint size,
                                 GLsizei stride,
                                 GLuint offset) {
  SetAttribute(name, size, stride, offset, false, GL_FLOAT);
}

/// @brief Assign shader vec3 uniform
/// @param x First vec3 component.
/// @param y Second vec3 component.
/// @param y Third vec3 component
/// @overload
void ShaderProgram::SetUniform(const std::string& name,
                               float x,
                               float y,
                               float z) {
  glUniform3f(Uniform(name), x, y, z);
}

/// @brief Assign shader vec3 uniform
/// @param v vec3 value
/// @overload
void ShaderProgram::SetUniform(const std::string& name, const vec3& v) {
  glUniform3fv(Uniform(name), 1, value_ptr(v));
}

/// @brief Assign shader vec4 uniform
/// @param v vec4 value
/// @overload
void ShaderProgram::SetUniform(const std::string& name, const vec4& v) {
  glUniform4fv(Uniform(name), 1, value_ptr(v));
}

/// @brief Assign shader mat4 uniform
/// @param m mat4 value
/// @overload
void ShaderProgram::SetUniform(const std::string& name, const mat4& m) {
  glUniformMatrix4fv(Uniform(name), 1, GL_FALSE, value_ptr(m));
}

/// @brief Assign shader mat3 uniform
/// @param m mat3 value
/// @overload
void ShaderProgram::SetUniform(const std::string& name, const mat3& m) {
  glUniformMatrix3fv(Uniform(name), 1, GL_FALSE, value_ptr(m));
}

/// @brief Assign shader float uniform
/// @param val float value
/// @overload
void ShaderProgram::SetUniform(const std::string& name, float val) {
  glUniform1f(Uniform(name), val);
}

/// @brief Assign shader int uniform
/// @param val int value
/// @overload
void ShaderProgram::SetUniform(const std::string& name, int val) {
  glUniform1i(Uniform(name), val);
}


/// @brief Bind the ShaderProgram. Future draw will use it. This unbind any
/// previously bound ShaderProgram.
void ShaderProgram::Use() const {
  glUseProgram(id());
}

/// @brief Unbind the ShaderProgram.
void ShaderProgram::Unuse() const {
  glUseProgram(0);
}

/// @brief The GPU id to the ShaderProgram.
/// @return The GPU id to the ShaderProgram.
GLuint ShaderProgram::id() const {
  return impl_->id;
}

bool ShaderProgram::operator==(const ShaderProgram& rhs) const {
  return impl_ == rhs.impl_;
}

bool ShaderProgram::operator!=(const ShaderProgram& rhs) const {
  return impl_ != rhs.impl_;
}

ShaderProgram::~ShaderProgram() = default;
ShaderProgram::ShaderProgram(ShaderProgram&&) noexcept = default;
ShaderProgram::ShaderProgram(const ShaderProgram&) = default;
ShaderProgram& ShaderProgram::operator=(ShaderProgram&&) noexcept = default;
ShaderProgram& ShaderProgram::operator=(const ShaderProgram&) = default;


}  // namespace smk
