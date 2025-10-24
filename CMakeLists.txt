cmake_minimum_required(VERSION 3.15)
project(MazeGame VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(
  maze
  src/main.c
  src/game.c
  src/args.c
  src/render.c
  src/parser.c
  src/helpers.c
  src/generator.c)

find_package(Curses REQUIRED)
if(CURSES_FOUND)
  target_link_libraries(maze PRIVATE ${CURSES_LIBRARIES})
  target_include_directories(maze PRIVATE ${CURSES_INCLUDE_DIR})
else()
  message(FATAL_ERROR "Curses library not found!")
endif()

target_compile_options(maze PRIVATE -O3)
target_include_directories(maze PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(MSVC)
  target_compile_options(maze PRIVATE /W4)
else()
  target_compile_options(maze PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(maze PRIVATE -Werror)
endif()
