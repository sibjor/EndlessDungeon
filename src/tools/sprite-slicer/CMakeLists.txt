# src/tools/sprite-slicer/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(sprite-slicer)

# Include SDL and SDL_image directories
include_directories(${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})

add_executable(sprite-slicer slicer.cpp)

# Link SDL and SDL_image libraries
target_link_libraries(sprite-slicer PRIVATE SDL3_image::SDL3_image SDL3::SDL3)