add_subdirectory(assets)

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
