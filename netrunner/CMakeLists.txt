cmake_minimum_required(VERSION 3.15)
project(netrunner C)

set(CMAKE_C_STANDARD 11)

add_executable(netrunner main.c server.c server.h)