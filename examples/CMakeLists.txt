add_subdirectory(assets)

if(EMSCRIPTEN)
  # Copy the index.html file.
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/index.html
    COPYONLY
  )
endif()

function(add_example target input)
  set(ns_target smk_example_${target})
  add_executable(${ns_target} ${input})
  set_target_properties(${ns_target} PROPERTIES OUTPUT_NAME ${target})
  target_link_libraries(${ns_target} PRIVATE smk smk_example_asset)
  set_property(TARGET ${ns_target} PROPERTY CXX_STANDARD 11)

  # Detect emscripten is used.
  if(EMSCRIPTEN)

    # Release flags
    set_property(TARGET ${ns_target} APPEND_STRING PROPERTY LINK_FLAGS
      " -s ALLOW_MEMORY_GROWTH=1"
      " -s DEMANGLE_SUPPORT=1"
      " -s DISABLE_EXCEPTION_CATCHING=2"
      " -s EXPORT_NAME='main' -s MODULARIZE=1"
    )
    set_property(GLOBAL APPEND_STRING PROPERTY LINK_FLAGS
      " -s WASM=1"
      " --js-opts 3"
      " --llvm-lto 3"
      " --llvm-opts 3"
      " -O3"
    )

    # Allow some files to be fetched.
    file(GLOB_RECURSE files "./assets/*")
    foreach(file ${files})
      file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} "${file}")
      set_property(TARGET ${ns_target} APPEND_STRING PROPERTY LINK_FLAGS " --preload-file \"${file}@/${relative_file}\"")
    endforeach()
  endif()
endfunction(add_example)

add_example(bezier bezier.cpp)
add_example(framebuffer framebuffer.cpp)
add_example(rounded_rectangle rounded_rectangle.cpp)
add_example(shape_2d shape_2d.cpp)
add_example(shape_3d shape_3d.cpp)
add_example(sound sound.cpp)
add_example(sprite sprite.cpp)
add_example(sprite_move sprite_move.cpp)
add_example(text text.cpp)
add_example(texture_subrectangle texture_subrectangle.cpp)
add_example(touch touch.cpp)
add_example(vibrate vibrate.cpp)
add_example(scroll scroll.cpp)
