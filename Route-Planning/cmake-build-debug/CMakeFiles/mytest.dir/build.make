# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/parallels/Documents/clion-2020.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/parallels/Documents/clion-2020.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/parallels/CppGithub/Route-Planning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/parallels/CppGithub/Route-Planning/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mytest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mytest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mytest.dir/flags.make

CMakeFiles/mytest.dir/mytest/main.cpp.o: CMakeFiles/mytest.dir/flags.make
CMakeFiles/mytest.dir/mytest/main.cpp.o: ../mytest/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/CppGithub/Route-Planning/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mytest.dir/mytest/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytest.dir/mytest/main.cpp.o -c /home/parallels/CppGithub/Route-Planning/mytest/main.cpp

CMakeFiles/mytest.dir/mytest/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytest.dir/mytest/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/parallels/CppGithub/Route-Planning/mytest/main.cpp > CMakeFiles/mytest.dir/mytest/main.cpp.i

CMakeFiles/mytest.dir/mytest/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytest.dir/mytest/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/parallels/CppGithub/Route-Planning/mytest/main.cpp -o CMakeFiles/mytest.dir/mytest/main.cpp.s

# Object files for target mytest
mytest_OBJECTS = \
"CMakeFiles/mytest.dir/mytest/main.cpp.o"

# External object files for target mytest
mytest_EXTERNAL_OBJECTS =

mytest: CMakeFiles/mytest.dir/mytest/main.cpp.o
mytest: CMakeFiles/mytest.dir/build.make
mytest: CMakeFiles/mytest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/parallels/CppGithub/Route-Planning/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mytest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mytest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mytest.dir/build: mytest

.PHONY : CMakeFiles/mytest.dir/build

CMakeFiles/mytest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mytest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mytest.dir/clean

CMakeFiles/mytest.dir/depend:
	cd /home/parallels/CppGithub/Route-Planning/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/parallels/CppGithub/Route-Planning /home/parallels/CppGithub/Route-Planning /home/parallels/CppGithub/Route-Planning/cmake-build-debug /home/parallels/CppGithub/Route-Planning/cmake-build-debug /home/parallels/CppGithub/Route-Planning/cmake-build-debug/CMakeFiles/mytest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mytest.dir/depend
