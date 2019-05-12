set(ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(asset.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/asset.hpp)
add_library(asset INTERFACE)
target_include_directories(asset INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
