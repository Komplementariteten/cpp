cmake_minimum_required(VERSION 3.12)
project(Geologger VERSION 0.9.01)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB UTIL_FILES ${CMAKE_SOURCE_DIR}/util/*.h)

set(SOURCE_FILES ${HEADERS} ${UTIL_FILES})

add_executable(Geologger main.cpp ${HEADERS})

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif(APPLE)

# Extern Global Libaries
# add_subdirectory(../Libary/leveldb)

include_directories(../Libary/leveldb/include)
LINK_DIRECTORIES(../Libary/leveldb/build)

add_subdirectory(server)
add_subdirectory(test)

target_link_libraries(Geologger udpserver leveldb)

install(TARGETS Geologger RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)
#target_link_libraries(GeoLogger udpserver)


