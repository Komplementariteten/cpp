cmake_minimum_required(VERSION 3.10)
project(NetScanner)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "/usr/local/Cellar/boost/1.66.0/")
find_package(Boost 1.66.0 REQUIRED)

set(SOURCE_FILES main.cpp NetScannerLib/netscanner.cpp NetScannerLib/netscanner.h NetScannerLib/ipv4_header.h NetScannerLib/icmp_header.h)
add_executable(NetScanner ${SOURCE_FILES})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(NetScanner ${Boost_LIBRARIES})
endif()

