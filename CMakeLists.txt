cmake_minimum_required(VERSION 3.23)
project(GUI)

set(CMAKE_CXX_STANDARD 14)
#[[set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")]]
link_libraries(libeasyx.a)
add_executable(GUI main.cpp Myprint.cpp Myprint.h)
