cmake_minimum_required(VERSION 3.16)
project(openai-cpp)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

option(BUILD_EXAMPLES "Build examples" OFF)
if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
