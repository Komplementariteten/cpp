cmake_minimum_required(VERSION 3.10.2)
project(tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(tests main.cpp)

add_executable(memrun1 mem1/main.cpp)