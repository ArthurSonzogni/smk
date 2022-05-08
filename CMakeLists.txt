cmake_minimum_required (VERSION 3.11)

project(smk
  LANGUAGES CXX
  VERSION 1.0.0
)

option(SMK_FETCH_DEPENDENCIES "Set to ON to fetch dependencies" ON)
option(SMK_BUILD_DOCS "Set to ON to build docs" ON)
option(SMK_BUILD_EXAMPLES "Set to ON to build examples" ON)
option(SMK_CLANG_TIDY "Execute clang-tidy" OFF)
option(SMK_ENABLE_INSTALL "Generate the install target" ON)

add_subdirectory(third_party)

add_library(stbimage OBJECT
  src/smk/StbImage.cpp
  src/smk/StbImage.hpp
)
target_include_directories(stbimage PRIVATE src/smk)

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
  target_compile_options(smk PRIVATE "-Wno-return-type")
endif()

set_property(TARGET smk PROPERTY CXX_STANDARD 17)

if(EMSCRIPTEN)
  target_link_libraries(smk PUBLIC "-s USE_GLFW=3")
  target_link_libraries(smk PUBLIC "-s USE_WEBGL2=1")
else()
  target_link_libraries(smk PUBLIC glfw)
  target_link_libraries(smk PUBLIC libglew_static)
  target_link_libraries(smk PRIVATE OpenAL)
endif()

target_link_libraries(smk PUBLIC $<BUILD_INTERFACE:glm>)
target_link_libraries(smk PRIVATE freetype)
target_link_libraries(smk PRIVATE libnyquist)
target_link_libraries(smk PRIVATE stbimage)

if(SMK_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(SMK_BUILD_DOCS)
  add_subdirectory(doc)
endif()

if (SMK_CLANG_TIDY)
  find_program( CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable" )
  if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
  else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set_target_properties(smk
      PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-warnings-as-errors=*"
    )
  endif()
endif()

if(SMK_ENABLE_INSTALL)
  include(cmake/smk_install.cmake)
  include(cmake/smk_package.cmake)
endif()
