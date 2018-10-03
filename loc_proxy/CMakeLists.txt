cmake_minimum_required(VERSION 3.12)
project(loc_proxy)

set(CMAKE_CXX_STANDARD 17)

add_executable(loc_proxy main.cpp tcp_proxy.cpp tcp_proxy.h)

# find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
# include_directories(${OpenCV_INCLUDE_DIRS})

#target_link_libraries(image_base ${OpenCV_LIBS})

#add_executable(erosamp eroding_sample/main.cpp)
#target_link_libraries(erosamp ${OpenCV_LIBS})
