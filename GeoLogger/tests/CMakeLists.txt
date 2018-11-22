cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(GeoLoggerTest)

file(GLOB TEST_FILES *Test.cpp)
set(SOURCE_FILES ${TESTS} ${TEST_FILES})

add_executable(Geologger_Tests TestGoogleTest.cpp catch.h TestNetTest.cpp TestCatchTest.cpp)
# target_link_libraries(Geologger_Tests gtest)
