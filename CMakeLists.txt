cmake_minimum_required(VERSION 3.0.0)
project(DATASTRUCTURE VERSION 0.1.0)

# INCLUDE(CMakeForceCompiler)
# CMAKE_FORCE_C_COMPILER(gcc GNU)
# CMAKE_FORCE_CXX_COMPILER(g++ GNU)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
include_directories(${PROJECT_SOURCE_DIR}/header)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

add_executable(datastruct main.c)

target_link_libraries(datastruct AllStructs)

