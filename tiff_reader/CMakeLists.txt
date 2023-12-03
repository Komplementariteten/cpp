cmake_minimum_required(VERSION 3.26)
project(tiff_reader)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests.cpp
        exporter.cpp
        tiff_reader.cpp
        cmd_tools.cpp
        cmd_tools.h
)
add_executable(data_tests
        data_tests.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(data_tests PRIVATE Catch2::Catch2WithMain)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
catch_discover_tests(data_tests)

add_executable(tiff_reader main.cpp
        exporter.cpp
        tiff_reader.cpp
        cmd_tools.cpp
        cmd_tools.h
)
