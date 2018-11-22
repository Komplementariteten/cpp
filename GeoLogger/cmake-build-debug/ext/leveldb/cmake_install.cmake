# Install script for directory: /Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/cmake-build-debug/ext/leveldb/libleveldb.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libleveldb.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libleveldb.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libleveldb.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/leveldb" TYPE FILE FILES
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/c.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/cache.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/comparator.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/db.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/dumpfile.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/env.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/export.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/filter_policy.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/iterator.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/options.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/slice.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/status.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/table_builder.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/table.h"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/include/leveldb/write_batch.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/leveldb/leveldbTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/leveldb/leveldbTargets.cmake"
         "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/cmake-build-debug/ext/leveldb/CMakeFiles/Export/lib/cmake/leveldb/leveldbTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/leveldb/leveldbTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/leveldb/leveldbTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/leveldb" TYPE FILE FILES "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/cmake-build-debug/ext/leveldb/CMakeFiles/Export/lib/cmake/leveldb/leveldbTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/leveldb" TYPE FILE FILES "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/cmake-build-debug/ext/leveldb/CMakeFiles/Export/lib/cmake/leveldb/leveldbTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/leveldb" TYPE FILE FILES
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/ext/leveldb/cmake/leveldbConfig.cmake"
    "/Users/me/Documents/Workspace/GitHub/Cpp/GeoLogger/cmake-build-debug/ext/leveldb/leveldbConfigVersion.cmake"
    )
endif()

