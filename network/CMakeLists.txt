cmake_minimum_required(VERSION 3.11)

project(net)

# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE PATTERN "complex/*.cc")
# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE FOLDER "complex")

file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

include_directories(${CMAKE_SOURCE_DIR}/include)

foreach(rle IN LISTS ALL_SAMPLE_SRCS)
	get_filename_component(rlename ${rle} NAME_WE)
	add_executable(${rlename} ${rle})
	if(WIN32)
		target_link_libraries(${rlename} PRIVATE ws2_32)
	endif(WIN32)
endforeach(rle IN LISTS ALL_SAMPLE_SRCS)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
