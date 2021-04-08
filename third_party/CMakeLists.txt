include(FetchContent)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "")

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(freetype2
  GIT_REPOSITORY https://github.com/aseprite/freetype2.git
  GIT_TAG VER-2-10-0
)

FetchContent_Declare(libnyquist
  #GIT_REPOSITORY https://github.com/ArthurSonzogni/libnyquist
  GIT_REPOSITORY https://github.com/ddiakopoulos/libnyquist
  GIT_TAG b05d6931ae5ffd1fa8b4e68807441b94cdcbc123
)

FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG fce2abd01ce21063bd25ba67c9318be83bf48813
)

FetchContent_Declare(glew
  #GIT_REPOSITORY https://github.com/ArthurSonzogni/glew-cmake
  #GIT_TAG 4b5f38fec0cee5640e06f550f2cbc8c7036aecb5
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
)

FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.3
)

FetchContent_Declare(openal
  GIT_REPOSITORY https://github.com/kcat/openal-soft
  GIT_TAG e123fa0ec349337ba4db00ebb2bbec1b7bee4cfa
)

FetchContent_GetProperties(freetype2)
if(NOT freetype2_POPULATED)
  FetchContent_Populate(freetype2)
  set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE)
  set(CMAKE_DISABLE_FIND_PACKAGE_BZip2 TRUE)
  set(CMAKE_DISABLE_FIND_PACKAGE_PNG TRUE)
  set(CMAKE_DISABLE_FIND_PACKAGE_ZLIB TRUE)
  add_subdirectory(${freetype2_SOURCE_DIR} ${freetype2_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(libnyquist)
if(NOT libnyquist_POPULATED)
  FetchContent_Populate(libnyquist)
  set(LIBNYQUIST_PULSE TRUE)
  set(BUILD_LIBOPUS TRUE)
  add_subdirectory(${libnyquist_SOURCE_DIR} ${libnyquist_BINARY_DIR} EXCLUDE_FROM_ALL)
  set_property(TARGET libopus PROPERTY CXX_STANDARD 17)
  target_compile_options(libnyquist PRIVATE "-w")
  target_compile_options(libopus PRIVATE "-w")
  target_compile_options(libwavpack PRIVATE "-w")
endif()

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED AND NOT EMSCRIPTEN)
  FetchContent_Populate(glew)
  option(glew-cmake_BUILD_SHARED "Build the shared glew library" OFF)
  set(glew-cmake_BUILD_SHARED OFF)
  add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED AND NOT EMSCRIPTEN)
  FetchContent_Populate(glfw)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
  target_compile_options(glfw PRIVATE "-w")
endif()

FetchContent_GetProperties(openal)
if(NOT openal_POPULATED AND NOT EMSCRIPTEN)
  FetchContent_Populate(openal)
  set(LIBTYPE STATIC)
  add_subdirectory(${openal_SOURCE_DIR} ${openal_BINARY_DIR} EXCLUDE_FROM_ALL)
  target_compile_options(OpenAL PRIVATE "-w")
endif()
