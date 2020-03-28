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

/// @brief A Shader is a little program that rest on the GPU. They are run on a
/// specific section of the graphic pipeline.
///
/// This is a move-only ressource.
///
/// @see https://learnopengl.com/Getting-started/Shaders
///
/// This class is independant from SMK.
///
/// ## Example:
///
/// ~~~cpp
/// auto vertex_shader = smk::Shader::FromString(R"(
///   layout(location = 0) in vec2 space_position;
///   layout(location = 1) in vec2 texture_position;
///   uniform mat4 projection;
///   uniform mat4 view;
///   out vec2 f_texture_position;
///   void main() {
///     f_texture_position = texture_position;
///     gl_Position = projection * view * vec4(space_position, 0.0, 1.0);
///   }
/// )", GL_VERTEX_SHADER);
///
/// auto fragment_shader = smk::Shader::FromString(R"(
///   in vec2 f_texture_position;
///   uniform sampler2D texture_0;
///   uniform vec4 color;
///   out vec4 out_color;
///   void main() {
///     vec4 color = texture(texture_0, f_texture_position) * color;
///     vec3 inverted_color = vec3(1.0) - color.rgb;
///     out_color = vec4(inverted_color, color.a);
///   }
/// )", GL_FRAGMENT_SHADER);
///
/// auto shader_program = smk::ShaderProgram();
/// shader_program.AddShader(vertex_shader);
/// shader_program.AddShader(fragment_shader);
/// shader_program.Link();
///
/// window.SetShaderProgram(&shader_program);
/// ~~~
//
/// @see ShaderProgram
class Shader {
 public:
  Shader();  // Invalid shader.
  static Shader FromFile(const std::string& filename, GLenum type);
  static Shader FromString(const std::string& content, GLenum type);

  // provide opengl shader identifiant.
  GLuint GetHandle() const;

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

/// @brief A shader program is a set of shader (for instance vertex shader +
/// pixel shader) defining the rendering pipeline.
///
/// This is a move-only ressource.
///
/// This class provide an interface to define the OpenGL uniforms and attributes
/// using GLM objects.
///
/// @see Shader
class ShaderProgram {
 public:
  ShaderProgram();
  void AddShader(const Shader& shader);
  void Link();

  // bind the program
  void Use() const;
  void Unuse() const;

  // provide the opengl identifiant
  GLuint GetHandle() const;

  // clang-format off
  // provide attributes informations.
  GLint Attribute(const std::string& name);
  void SetAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize, GLenum type);
  void SetAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize);
  void SetAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLenum type); 
  void SetAttribute(const std::string& name, GLint size, GLsizei stride, GLuint offset);
  // clang-format on

  // provide uniform location
  GLint Uniform(const std::string& name);
  GLint operator[](const std::string& name);

  // affect uniform
  void SetUniform(const std::string& name, float x, float y, float z);
  void SetUniform(const std::string& name, const glm::vec3& v);
  void SetUniform(const std::string& name, const glm::vec4& v);
  void SetUniform(const std::string& name, const glm::mat4& m);
  void SetUniform(const std::string& name, const glm::mat3& m);
  void SetUniform(const std::string& name, float val);
  void SetUniform(const std::string& name, int val);

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
