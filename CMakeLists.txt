cmake_minimum_required(VERSION 3.16)
project(EndlessDungeon)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the output directory for built objects.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)

# On Web targets, we need CMake to generate a HTML webpage
if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

# Create your game executable target as usual
add_executable(EndlessDungeon src/main.cpp src/tools/sprite-slicer/slicer.cpp)

# Link to the actual SDL3 library
target_link_libraries(EndlessDungeon PRIVATE SDL3_image::SDL3_image SDL3::SDL3)

# Copy compile_commands.json to root directory if different
add_custom_command(TARGET EndlessDungeon POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)