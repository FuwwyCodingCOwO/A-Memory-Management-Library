cmake_minimum_required(VERSION 3.28.3)
project(idk C)

set(CMAKE_C_STANDARD 17)

add_library(manager STATIC manager.c)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE manager)