cmake_minimum_required(VERSION 3.11)

project(cbase)

# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE PATTERN "complex/*.cc")
# file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc EXCLUDE FOLDER "complex")

file(GLOB_RECURSE ALL_SAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

foreach(rle IN LISTS ALL_SAMPLE_SRCS)
	get_filename_component(rlename ${rle} NAME_WE)
	#add_definitions(-D-Wwrite-strings)

	add_executable(${rlename} ${rle})
	if(WIN32)
		add_compile_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
		target_link_libraries(${rlename} PRIVATE ws2_32)
	elseif(UNIX)
        add_compile_options(-Wno-write-strings)
	endif(WIN32)
	
endforeach(rle IN LISTS ALL_SAMPLE_SRCS)
