add_subdirectory(assets)

add_executable(sound sound.cpp)
target_link_libraries(sound PRIVATE smk asset)

add_executable(sprite sprite.cpp)
target_link_libraries(sprite PRIVATE smk asset)

add_executable(text text.cpp)
target_link_libraries(text PRIVATE smk asset)

add_executable(shape shape.cpp)
target_link_libraries(shape PRIVATE smk asset)
