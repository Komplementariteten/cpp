cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(Geologger_Test)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(GTEST_PATH "../ext/googletest-release-1.8.1" CACHE PATH "Google Test Suite Path")

add_subdirectory(${GTEST_PATH})

include_directories(${GTEST_PATH}/googletest/include)
include_directories(${GTEST_PATH}/googlemock/include)


file(GLOB TEST_FILE *Test.cpp)
set(SOURCE_FILES ${TESTS} ${TEST_FILES})

include_directories(/Users/me/Documents/libaries/leveldb/include)

add_executable(geologger_test main.cpp GtestTest.cpp LeveldbTest.cpp SocketTest.cpp ThreadTest.cpp UdpServerTest.cpp)
target_link_libraries(geologger_test gtest gmock)
target_link_libraries(geologger_test udpserver)
target_link_libraries(geologger_test leveldb)

if(Boost_FOUND)
    target_link_libraries(geologger_test ${Boost_LIBRARIES})
endif()