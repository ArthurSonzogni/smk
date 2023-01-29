include(FetchContent)

SET(BUILD_SHARED_LIBS OFF CACHE BOOL "")

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(freetype2
  GIT_REPOSITORY https://github.com/aseprite/freetype2.git
  GIT_TAG VER-2-10-0
  GIT_PROGRESS TRUE
)

FetchContent_Declare(libnyquist
  GIT_REPOSITORY https://github.com/ddiakopoulos/libnyquist
  GIT_TAG b05d6931ae5ffd1fa8b4e68807441b94cdcbc123
  GIT_SHALLOW FALSE
  GIT_PROGRESS TRUE
)

FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # 0.9.9.8
  GIT_PROGRESS TRUE
)

FetchContent_Declare(glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
  GIT_TAG f456deace7b408655109aaeff71421ef2d3858c6 # 2.2.0
  GIT_PROGRESS TRUE
)

FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 45ce5ddd197d5c58f50fdd3296a5131c894e5527 # 3.3.7
  GIT_PROGRESS TRUE
)

FetchContent_Declare(openal
  GIT_REPOSITORY https://github.com/kcat/openal-soft
  GIT_TAG c1c63a27de66cd44ef756b190a73bfa8bc6dbbab # 1.22.0
  GIT_PROGRESS TRUE
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
  set(LIBNYQUIST_BUILD_EXAMPLE OFF)
  set(BUILD_LIBOPUS TRUE)
  set(BUILD_LIBWAVPACK TRUE)
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
