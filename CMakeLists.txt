cmake_minimum_required(VERSION 3.16)
project(EndlessDungeon)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
set(SOURCES
  src/main.cpp
  src/game.cpp
  src/dungeon.cpp
  src/metadata.h
  src/utils/texture_loader.c
  src/utils/random.cpp
)

# Spritesheet slicer executable
add_executable(SpritesheetSlicer src/tools/spritesheet/slicer.c)

# Client Executable
add_executable(EndlessDungeon ${SOURCES})
target_link_libraries(EndlessDungeon PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Emscripten specific settings
if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-wasm/$<CONFIGURATION>")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-wasm/$<CONFIGURATION>")
  set_target_properties(EndlessDungeon PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-wasm")
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-client/$<CONFIGURATION>")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-client/$<CONFIGURATION>")
  set_target_properties(EndlessDungeon PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-client")
endif()

# Copy compile_commands.json to root directory if different
add_custom_command(TARGET EndlessDungeon POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)

add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)