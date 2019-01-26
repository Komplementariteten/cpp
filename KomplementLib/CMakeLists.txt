cmake_minimum_required(VERSION 3.12)
project(KomplementLib)

set(CMAKE_CXX_STANDARD 17)

add_library(KomplementLib SHARED library.cpp library.h net.h type_tools.h)

# install(TARGETS KomplementLib DESTINATION lib)

# install(TARGETS library.h net.h type_tools.h DESTINATION include)

add_executable(test_runner tests/test_runner.cpp tests/catch.hpp)

target_link_libraries(test_runner KomplementLib)
