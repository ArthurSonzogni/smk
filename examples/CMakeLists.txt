add_subdirectory(assets)

if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 
  # Copy the index.html file.
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/index.html
    COPYONLY
  )
endif()

function(add_example target input)
  add_executable(${target} ${input})
  target_link_libraries(${target} PRIVATE smk asset)
  set_property(TARGET ${target} PROPERTY CXX_STANDARD 11)

  # Detect emscripten is used.
  if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") 

    # Release flags
    #set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -s ALLOW_MEMORY_GROWTH=1")
    #set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -s DEMANGLE_SUPPORT=1")
    #set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -s DISABLE_EXCEPTION_CATCHING=2")
    set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -s EXPORT_NAME='emscripten'")
    set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " -s MODULARIZE=1")
    #set_property(GLOBAL APPEND_STRING PROPERTY LINK_FLAGS " -s WASM=1")
    #set_property(GLOBAL APPEND_STRING PROPERTY LINK_FLAGS  " --js-opts 3")
    #set_property(GLOBAL APPEND_STRING PROPERTY LINK_FLAGS  " --llvm-lto 3")
    #set_property(GLOBAL APPEND_STRING PROPERTY LINK_FLAGS  " --llvm-opts 3")
    #set_property(GLOBAL APPEND_STRING PROPERTY LINK_FLAGS  " -O3")

  set(CXX_FLAGS "CXX FLAGS EMCC_DEBUG=1 -g")
  set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS  " -s WASM=1")
  set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS  " -s TOTAL_MEMORY=134217728")

    # Allow some files to be fetched.
    file(GLOB_RECURSE files "./assets/*")
    foreach(file ${files})
      file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} "${file}")
      set_property(TARGET ${target} APPEND_STRING PROPERTY LINK_FLAGS " --preload-file \"${file}@/${relative_file}\"")
    endforeach()
  endif()
endfunction(add_example)

add_example(shape_2d shape_2d.cpp)
add_example(shape_3d shape_3d.cpp)
add_example(sound sound.cpp)
add_example(sprite sprite.cpp)
add_example(sprite_move sprite_move.cpp)
add_example(text text.cpp)
add_example(texture_subrectangle texture_subrectangle.cpp)
add_example(framebuffer framebuffer.cpp)
add_example(touch touch.cpp)
