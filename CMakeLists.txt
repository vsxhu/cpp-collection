project(cpp-collection)
cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

option(ENABLE_TOYS "Build toys" ON)
option(ENABLE_REFL "Build reflection" ON)
option(ENABLE_GRAPH "Build async graph" ON)
option(ENABLE_BINARY "Build Binary" ON)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(app)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
