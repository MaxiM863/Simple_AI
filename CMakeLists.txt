cmake_minimum_required (VERSION 3.10)

project(AI)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(vendor)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE SDL3::SDL3)