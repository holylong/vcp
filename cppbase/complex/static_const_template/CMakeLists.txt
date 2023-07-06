cmake_minimum_required(VERSION 3.5)

project(static_const_template)

set(CMAKE_CXX_STANDARD 17)

file(GLOB sct_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
message(STATUS ${sct_SRCS})
add_executable(${PROJECT_NAME} ${sct_SRCS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})