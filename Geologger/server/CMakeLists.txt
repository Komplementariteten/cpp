cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(UdpServer)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_library(udpserver STATIC udp_server.cpp)
install(TARGETS udpserver DESTINATION lib)
install(FILES udp_server.h DESTINATION include)
target_include_directories(udpserver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(Boost_FOUND)
    target_link_libraries(udpserver ${Boost_LIBRARIES})
endif()
