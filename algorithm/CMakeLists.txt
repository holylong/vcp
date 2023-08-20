cmake_minimum_required(VERSION 3.11)

project(algorithm)

# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE PATTERN "complex/*.cc")
# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE FOLDER "complex")

file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

foreach(rle IN LISTS ALL_SAMPLE_SRCS)
	get_filename_component(rlename ${rle} NAME_WE)
	#add_definitions(-D-Wwrite-strings)
	if(WIN32)
		add_compile_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
	elseif(UNIX)
        add_compile_options(-Wno-write-strings)
	endif(WIN32)
	add_executable(${rlename} ${rle})
endforeach(rle IN LISTS ALL_SAMPLE_SRCS)
