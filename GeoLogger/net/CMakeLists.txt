cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(Libnet)


file(GLOB UTIL_FILES ${CMAKE_SOURCE_DIR}/util/*.h)
set(SOURCE_FILES ${HEADERS} ${UTIL_FILES})
add_library(net STATIC ${HEADERS} udp_server.cpp)