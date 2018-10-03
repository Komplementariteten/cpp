cmake_minimum_required(VERSION 3.12)
project(image_base)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(image_base main.cpp image_handle.cpp image_handle.h)
target_link_libraries(image_base ${OpenCV_LIBS})

add_executable(erosamp eroding_sample/main.cpp)
target_link_libraries(erosamp ${OpenCV_LIBS})
