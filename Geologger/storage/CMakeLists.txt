cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(DbStorage)

file(GLOB UTIL_FILES ${CMAKE_SOURCE_DIR}/util/*.h)
set(SOURCE_FILES ${HEADERS} ${UTIL_FILES})


add_library(DbStorage STATIC ${HEADERS} dbstorage.cpp)
install(TARGETS DbStorage DESTINATION lib)
install(FILES dbstorage.h DESTINATION include)
target_include_directories(DbStorage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(DbStorage leveldb)