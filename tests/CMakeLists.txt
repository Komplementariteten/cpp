cmake_minimum_required(VERSION 3.10.2)
project(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")


add_executable(tests main.cpp)

add_executable(memrun1 mem1/main.cpp)
add_executable(raii_example raii/main.cpp)
add_executable(move_example move/main.cpp)
add_executable(thread_example threadtest/main.cpp)
add_executable(lambdas_example lambdas/main.cpp)
add_executable(task_example taskstest/main.cpp)