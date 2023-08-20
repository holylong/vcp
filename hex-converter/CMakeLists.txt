cmake_minimum_required(VERSION 3.11)

project(hexcvt VERSION 0.1.1)


file(GLOB hexcvt_SRC main.cc)

add_executable(${PROJECT_NAME} ${hexcvt_SRC})