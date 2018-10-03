cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(Geologger_Test)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()


include_directories(/Users/me/Documents/libaries/googletest-release-1.8.1/include)

add_executable(geologger_test main.cpp GtestTest.cpp SocketTest.cpp ThreadTest.cpp)
target_link_libraries(geologger_test gtest gmock)
target_link_libraries(geologger_test udpserver)

if(Boost_FOUND)
    target_link_libraries(geologger_test ${Boost_LIBRARIES})
endif()