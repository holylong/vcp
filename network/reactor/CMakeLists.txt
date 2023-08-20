cmake_minimum_required(VERSION 3.11)

project(reactor)

aux_source_directory(. Reactor_SRCS)
message(STATUS ${Reactor_SRCS})
add_executable(${PROJECT_NAME} ${Reactor_SRCS})

if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif(WIN32)
