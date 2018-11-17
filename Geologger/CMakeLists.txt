cmake_minimum_required(VERSION 3.12)
project(Geologger VERSION 0.9.01)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB UTIL_FILES ${CMAKE_SOURCE_DIR}/util/*.h)

set(SOURCE_FILES ${HEADERS} ${UTIL_FILES})

add_executable(Geologger main.cpp ${HEADERS})

# Extern Global Libaries
add_subdirectory(ext/leveldb)
include_directories(ext/leveldb/include)


add_subdirectory(server)
add_subdirectory(test)

target_link_libraries(Geologger udpserver)

install(TARGETS Geologger RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)
#target_link_libraries(GeoLogger udpserver)


