cmake_minimum_required(VERSION 3.16)
project(SpritesheetSlicer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
set(SOURCES
  slicer.c
)

# Client Executable
add_executable(SpritesheetSlicer ${SOURCES})
target_link_libraries(SpritesheetSlicer PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Copy compile_commands.json to root directory if different
add_custom_command(TARGET SpritesheetSlicer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)

add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)