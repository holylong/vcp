cmake_minimum_required(VERSION 3.11)

project(designpattern VERSION 0.0.1 LANGUAGES CXX)

file(GLOB_RECURSE PATTERN_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)

message(STATUS ${PATTERN_SRCS})
foreach(item IN LISTS PATTERN_SRCS)
    get_filename_component(itemname ${item} NAME_WE)
    add_executable(${itemname} ${item})
endforeach(item IN LISTS PATTERN_SRCS)
