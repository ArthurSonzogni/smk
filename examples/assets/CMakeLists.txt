set(ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR})
configure_file(asset.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/asset.hpp)
add_library(asset asset.cpp)
target_include_directories(asset PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
