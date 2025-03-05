cmake_minimum_required(VERSION 3.16)
project(EndlessDungeon)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
set(SOURCES
  # C++
    src/main.cpp
    src/dungeon_generator.cpp
    src/game_wrapper.cpp
  # C
    src/utils/dir_utils.c
    src/utils/file_utils.c
    src/utils/texture_loader.c
    src/tools/spritesheet/slicer.c
)

if(SERVER)
  # Server-specific source files
  list(APPEND SOURCES
    src/tools/server/server.c
  )
  
  # Set the output directory for built objects.
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-server/$<CONFIGURATION>")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-server/$<CONFIGURATION>")

  # Server Executable
  add_executable(EndlessDungeonServer ${SOURCES})
  target_link_libraries(EndlessDungeonServer PRIVATE CURL::libcurl SDL3_image::SDL3_image SDL3::SDL3)
  set_target_properties(EndlessDungeonServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-server")

  # Copy compile_commands.json to root directory if different
  add_custom_command(TARGET EndlessDungeonServer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
  )
endif()

if(CLIENT)
  # Client-specific source files
  list(APPEND SOURCES
    # Add client-specific source files here
  )
  
  # Set the output directory for built objects.
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-client/$<CONFIGURATION>")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-client/$<CONFIGURATION>")

  # Client Executable
  add_executable(EndlessDungeonClient ${SOURCES})
  target_link_libraries(EndlessDungeonClient PRIVATE SDL3_image::SDL3_image SDL3::SDL3)
  set_target_properties(EndlessDungeonClient PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-client")

  # Copy compile_commands.json to root directory if different
  add_custom_command(TARGET EndlessDungeonClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
  )
endif()

if(EMSCRIPTEN)
  # Set the output directory for built objects.
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-wasm/$<CONFIGURATION>")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-wasm/$<CONFIGURATION>")

  # On Web targets, we need CMake to generate a HTML webpage
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")

  # Wasm Executable
  add_executable(EndlessDungeonWeb ${SOURCES})
  target_link_libraries(EndlessDungeonWeb PRIVATE SDL3_image::SDL3_image SDL3::SDL3)
  set_target_properties(EndlessDungeonWeb PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build-wasm")

  # Copy compile_commands.json to root directory if different
  add_custom_command(TARGET EndlessDungeonWeb POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
  )
endif()

add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(libcurl EXCLUDE_FROM_ALL)