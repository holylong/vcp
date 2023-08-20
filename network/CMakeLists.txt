cmake_minimum_required(VERSION 3.11)

project(net)

# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE PATTERN "complex/*.cc")
# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE FOLDER "complex")

file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

include_directories(${CMAKE_SOURCE_DIR}/include)

if(WIN32)
	list(REMOVE_ITEM ALL_SAMPLE_SRCS epoll_demo.cc)
elseif(UNIX)
	list(REMOVE_ITEM ALL_SAMPLE_SRCS iocp_demo.cc)
endif(WIN32)

list(REMOVE_ITEM ALL_SAMPLE_SRCS reactor/Reactor.cc reactor/SocketHandler.cc reactor/main.cc)

message(STATUS ${ALL_SAMPLE_SRCS})

foreach(rle IN LISTS ALL_SAMPLE_SRCS)
	get_filename_component(rlename ${rle} NAME_WE)
	add_executable(${rlename} ${rle})
	if(WIN32)
		target_link_libraries(${rlename} PRIVATE ws2_32)
		add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
		add_compile_definitions(_WINSOCK_DEPRECATED_NO_WARNINGS)
	endif(WIN32)
endforeach(rle IN LISTS ALL_SAMPLE_SRCS)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})


add_subdirectory(reactor)