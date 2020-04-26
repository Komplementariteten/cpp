cmake_minimum_required(VERSION 3.15)
project(audiobackend)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS CACHE STRING "-I/usr/local/opt/llvm/include" FORCE)
# set(CMAKE_EXE_LINKER_FLAGS CACHE STRING "-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib" FORCE)

add_executable(audiobackend main.cpp)