cmake_minimum_required(VERSION 3.5)
project(Path-Tracing
  LANGUAGES CXX
  VERSION 1.0
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(COPY
    "${CMAKE_SOURCE_DIR}/src/shader.glsl"
    DESTINATION "${CMAKE_BINARY_DIR}/"
)

add_subdirectory(libs)
add_subdirectory(src)
target_include_directories(Path-Tracing PRIVATE include)
