// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_SHADER_HPP
#define SMK_SHADER_HPP

#include <glm/glm.hpp>
#include <initializer_list>
#include <map>
#include <smk/OpenGL.hpp>
#include <string>
#include <vector>

namespace smk {

class Shader;
class ShaderProgram;

// Loads a shader from a file into OpenGL.
class Shader {
 public:
  Shader();  // Invalid shader.
  static Shader FromFile(const std::string& filename, GLenum type);
  static Shader FromString(const std::string& content, GLenum type);

  // provide opengl shader identifiant.
  GLuint getHandle() const;

  ~Shader();

  // --- Move only resource ----------------------------------------------------
  Shader(Shader&&);
  Shader(const Shader&) = delete;
  void operator=(Shader&&);
  void operator=(const Shader&) = delete;
  // ---------------------------------------------------------------------------

 private:
  Shader(std::vector<char> content, GLenum type);
  // opengl program identifiant
  GLuint handle_ = 0;

  friend class ShaderProgram;
};

// A shader program is a set of shader (for instance vertex shader + pixel
// shader) defining the rendering pipeline.
//
// This class provide an interface to define the OpenGL uniforms and attributes
// using GLM objects.
class ShaderProgram {
 public:
  ShaderProgram();

  void AddShader(const Shader& shader);
  void Link();

  // bind the program
  void use() const;
  void unuse() const;

  // provide the opengl identifiant
  GLuint getHandle() const;

  // clang-format off
  // provide attributes informations.
  GLint attribute(const std::string& name);
  void setAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize, GLenum type);
  void setAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize);
  void setAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLenum type); 
  void setAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset);
  // clang-format on

  // provide uniform location
  GLint uniform(const std::string& name);
  GLint operator[](const std::string& name);

  // affect uniform
  void setUniform(const std::string& name, float x, float y, float z);
  void setUniform(const std::string& name, const glm::vec3& v);
  void setUniform(const std::string& name, const glm::vec4& v);
  void setUniform(const std::string& name, const glm::mat4& m);
  void setUniform(const std::string& name, const glm::mat3& m);
  void setUniform(const std::string& name, float val);
  void setUniform(const std::string& name, int val);

  ~ShaderProgram();

  // --- Move only resource ----------------------------------------------------
  ShaderProgram(ShaderProgram&&);
  ShaderProgram(const ShaderProgram&) = delete;
  void operator=(ShaderProgram&&);
  void operator=(const ShaderProgram&) = delete;
  // ---------------------------------------------------------------------------

 private:
  std::map<std::string, GLint> uniforms_;

  // opengl id
  GLuint handle_ = 0;
};

}  // namespace smk

#endif  // SMK_SHADER_HPP
