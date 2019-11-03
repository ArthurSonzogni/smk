add_subdirectory(assets)

# Detect emscripten is used.
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 
  # Copy the index.html file.
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/index.html
  )

  string(APPEND CMAKE_CXX_FLAGS " -s ALLOW_MEMORY_GROWTH=1")
  string(APPEND CMAKE_CXX_FLAGS " -s BINARYEN_TRAP_MODE='allow'")
  string(APPEND CMAKE_CXX_FLAGS " -s DEMANGLE_SUPPORT=1")
  string(APPEND CMAKE_CXX_FLAGS " -s DISABLE_EXCEPTION_CATCHING=2")
  string(APPEND CMAKE_CXX_FLAGS " -s EXPORT_NAME='emscripten'")
  string(APPEND CMAKE_CXX_FLAGS " -s MODULARIZE=1")
  string(APPEND CMAKE_CXX_FLAGS " -s WASM=1")

  # Allow some files to be fetched.
  file(GLOB_RECURSE files "./assets/*")
  foreach(file ${files})
    file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} "${file}")
    string(APPEND CMAKE_CXX_FLAGS " --preload-file \"${file}@/${relative_file}\"")
    message(STATUS CMAKE_CXX_FLAGS " --preload-file \"${file}@/${relative_file}\"")
  endforeach()
endif()

add_executable(sound sound.cpp)
target_link_libraries(sound PRIVATE smk asset)
set_property(TARGET sound PROPERTY CXX_STANDARD 11)

add_executable(sprite sprite.cpp)
target_link_libraries(sprite PRIVATE smk asset)
set_property(TARGET sprite PROPERTY CXX_STANDARD 11)

add_executable(sprite_move sprite_move.cpp)
target_link_libraries(sprite_move PRIVATE smk asset)
set_property(TARGET sprite_move PROPERTY CXX_STANDARD 11)

add_executable(texture_subrectangle texture_subrectangle.cpp)
target_link_libraries(texture_subrectangle PRIVATE smk asset)
set_property(TARGET texture_subrectangle PROPERTY CXX_STANDARD 11)

add_executable(text text.cpp)
target_link_libraries(text PRIVATE smk asset)
set_property(TARGET text PROPERTY CXX_STANDARD 11)

add_executable(shape_2d shape_2d.cpp)
target_link_libraries(shape_2d PRIVATE smk asset)
set_property(TARGET shape_2d PROPERTY CXX_STANDARD 11)

add_executable(shape_3d shape_3d.cpp)
target_link_libraries(shape_3d PRIVATE smk asset)
set_property(TARGET shape_3d PROPERTY CXX_STANDARD 11)
