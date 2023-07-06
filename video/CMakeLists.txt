cmake_minimum_required(VERSION 3.11)

project(ffplayer LANGUAGES C)

if(WIN32)
    find_package(SDL2 QUIET CONFIG REQUIRED)
    find_package(ffmpeg QUIET REQUIRED)
    find_package(SDL2_ttf QUIET CONFIG REQUIRED)

    include_directories(${FFMPEG_INCLUDE_DIRS})
endif(WIN32)

add_executable(ffplayer src/ffplayer.c)
add_executable(tutorial01 src/tutorial01.c)

if(UNIX)
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/install/include/SDL2)
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/install/include)
    
    target_compile_options(ffplayer PRIVATE -Wno-deprecated-declarations)
    target_link_libraries(ffplayer PRIVATE swscale avformat avcodec avutil)

    target_compile_options(tutorial01 PRIVATE -Wno-deprecated-declarations)
    target_link_libraries(tutorial01 PRIVATE swscale avformat avcodec avutil)
endif(UNIX)

if(WIN32)   
    target_link_libraries(tutorial01 PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf-static)
    target_link_libraries(tutorial01 PRIVATE ${FFMPEG_LIBRARIES})

    target_link_libraries(ffplayer PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf-static)
    target_link_libraries(ffplayer PRIVATE ${FFMPEG_LIBRARIES})
endif(WIN32)

file(GLOB_RECURSE PLAYER_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
list(REMOVE_ITEM PLAYER_SRCS ffplayer.c tutorial01.c ffplay.c)
foreach(item IN LISTS PLAYER_SRCS)
    message(STATUS "==>> ${item}")
    get_filename_component(itemname ${item} NAME_WE)

    add_executable(${itemname} ${CMAKE_CURRENT_SOURCE_DIR}/src/${item})
if(UNIX)
    target_compile_options(${itemname} PRIVATE -Wno-deprecated-declarations -Wno-implicit-function-declaration)
    target_link_libraries(${itemname} PRIVATE swscale avformat avcodec avutil SDL2 SDL2main avdevice)
elseif(WIN32)
    target_link_libraries(${itemname} PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf-static)
    target_link_libraries(${itemname} PRIVATE ${FFMPEG_LIBRARIES})
endif(UNIX)


endforeach(item IN LISTS PLAYER_SRCS)
