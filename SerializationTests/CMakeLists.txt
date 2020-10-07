cmake_minimum_required(VERSION 3.17)
project(SerializationTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RULE_MESSAGES OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(SerializationTests main.cpp include/datatypes.h Server/ServerSocket.h include/functions.h)