cmake_minimum_required(VERSION 3.12)
project(Cpp)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(sample01)

add_subdirectory(image_base)

add_subdirectory(loc_proxy)

add_executable(Cpp main.cpp)