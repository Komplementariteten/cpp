cmake_minimum_required(VERSION 3.12)
project(GeoLogger)

set(CMAKE_CXX_STANDARD 17)

#LevelDB
add_subdirectory(ext/leveldb)
include_directories(ext/leveldb/include)

# Google Test
# add_subdirectory(ext/googletest)
# include_directories(ext/googletest/googletest/include)
# include_directories(ext/googletest/googlemock/include)


# Unit Testing
add_subdirectory(tests)
add_subdirectory(net)