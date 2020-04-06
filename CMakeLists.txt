cmake_minimum_required (VERSION 3.11)

# Configure dependencies for build static libraries only. 
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(third_party)

project(smk
  LANGUAGES CXX
  VERSION 0.1.0
)

add_library(smk STATIC
  include/smk/Audio.hpp
  include/smk/BlendMode.hpp
  include/smk/Color.hpp
  include/smk/Drawable.hpp
  include/smk/Font.hpp
  include/smk/Framebuffer.hpp
  include/smk/Input.hpp
  include/smk/OpenGL.hpp
  include/smk/Rectangle.hpp
  include/smk/RenderState.hpp
  include/smk/RenderTarget.hpp
  include/smk/Shader.hpp
  include/smk/Shape.hpp
  include/smk/Sound.hpp
  include/smk/SoundBuffer.hpp
  include/smk/Sprite.hpp
  include/smk/Text.hpp
  include/smk/Texture.hpp
  include/smk/Touch.hpp
  include/smk/Transformable.hpp
  include/smk/Vertex.hpp
  include/smk/VertexArray.hpp
  include/smk/Vibrate.hpp
  include/smk/View.hpp
  include/smk/Window.hpp
  src/smk/Audio.cpp
  src/smk/BlendMode.cpp
  src/smk/Color.cpp
  src/smk/Font.cpp
  src/smk/Framebuffer.cpp
  src/smk/InputImpl.cpp
  src/smk/InputImpl.cpp
  src/smk/RenderTarget.cpp
  src/smk/Shader.cpp
  src/smk/Shape.cpp
  src/smk/Sound.cpp
  src/smk/SoundBuffer.cpp
  src/smk/Sprite.cpp
  src/smk/StbImage.cpp
  src/smk/StbImage.hpp
  src/smk/Text.cpp
  src/smk/Texture.cpp
  src/smk/Touch.cpp
  src/smk/Transformable.cpp
  src/smk/Vertex.cpp
  src/smk/VertexArray.cpp
  src/smk/Vibrate.cpp
  src/smk/View.cpp
  src/smk/Window.cpp
)
add_library(smk::smk ALIAS smk)

target_include_directories(smk
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    src/
)

# Add as many warning as possible:
if (MSVC)
  target_compile_options(smk PRIVATE "/wd4244")
  target_compile_options(smk PRIVATE "/wd4267")
  target_compile_options(smk PRIVATE "/wd4996")
  target_compile_options(smk PRIVATE "/wd4305")
else()
  target_compile_options(smk PRIVATE "-Wall")
  target_compile_options(smk PRIVATE "-Werror")
  target_compile_options(smk PRIVATE "-Wno-sign-compare")
endif()

set_property(TARGET smk PROPERTY CXX_STANDARD 17)

if(EMSCRIPTEN)
  target_link_libraries(smk PUBLIC "-s USE_GLFW=3")
  target_link_libraries(smk PUBLIC "-s USE_WEBGL2=1")
else()
  target_link_libraries(smk PUBLIC glfw)
  target_link_libraries(smk PUBLIC libglew_static)
  target_link_libraries(smk PUBLIC OpenAL)
endif()

target_link_libraries(smk PUBLIC glm)
target_link_libraries(smk PRIVATE freetype)
target_link_libraries(smk PRIVATE libnyquist)

add_subdirectory(examples)
add_subdirectory(doc)
