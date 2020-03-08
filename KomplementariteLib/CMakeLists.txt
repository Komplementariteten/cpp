cmake_minimum_required(VERSION 3.15)
project(KomplementariteLib)

set(CMAKE_CXX_STANDARD 20)

add_library(KomplementariteLib library.cpp library.h observers.h tests.h)