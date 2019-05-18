include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# ------------------------------------------------------------------------------
# Freetype library for loading fonts.
# ------------------------------------------------------------------------------
FetchContent_Declare(freetype2
  GIT_REPOSITORY https://github.com/aseprite/freetype2.git
  GIT_TAG VER-2-10-0
)

FetchContent_GetProperties(freetype2)
if(NOT freetype2_POPULATED)
  FetchContent_Populate(freetype2)
  add_subdirectory(${freetype2_SOURCE_DIR} ${freetype2_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------
# Libnyquist library for loading sounds.
# ------------------------------------------------------------------------------
FetchContent_Declare(libnyquist
  GIT_REPOSITORY https://github.com/ArthurSonzogni/libnyquist
  )

FetchContent_GetProperties(libnyquist)
if(NOT libnyquist_POPULATED)
  FetchContent_Populate(libnyquist)
  set(LIBNYQUIST_PULSE TRUE)
  add_subdirectory(${libnyquist_SOURCE_DIR} ${libnyquist_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------
# GLM for matrix / vector manipulation
# ------------------------------------------------------------------------------
FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG fce2abd01ce21063bd25ba67c9318be83bf48813
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT EMSCRIPTEN)
  # ----------------------------------------------------------------------------
  # Glew for resolving OpenGL function at runtime.
  # ----------------------------------------------------------------------------
  FetchContent_Declare(glew
    GIT_REPOSITORY https://github.com/ArthurSonzogni/glew-cmake
    GIT_TAG 4b5f38fec0cee5640e06f550f2cbc8c7036aecb5
  )

  FetchContent_GetProperties(glew)
  if(NOT glew_POPULATED)
    FetchContent_Populate(glew)
    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()

  # ----------------------------------------------------------------------------
  # GLFW2 for getting a new window from the OS in a cross platform way.
  # ----------------------------------------------------------------------------
  FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.3
  )

  FetchContent_GetProperties(glfw)
  if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()

  # ----------------------------------------------------------------------------
  # OpenAL for communicating with the OS for Audio
  # ----------------------------------------------------------------------------
  FetchContent_Declare(openal
    GIT_REPOSITORY https://github.com/arthursonzogni/openal-soft
    GIT_TAG 5e2e4d50d324f713a7c39cdc71ce9050d2c34b5e
  )

  FetchContent_GetProperties(openal)
  if(NOT openal_POPULATED)
    FetchContent_Populate(openal)
    set(LIBTYPE STATIC)
    add_subdirectory(${openal_SOURCE_DIR} ${openal_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()
