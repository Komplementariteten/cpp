# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.12.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.12.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/me/Documents/Workspace/GitHub/Cpp/Geologger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug

# Include any dependencies generated for this target.
include ext/leveldb/CMakeFiles/version_set_test.dir/depend.make

# Include the progress variables for this target.
include ext/leveldb/CMakeFiles/version_set_test.dir/progress.make

# Include the compile flags for this target's objects.
include ext/leveldb/CMakeFiles/version_set_test.dir/flags.make

ext/leveldb/CMakeFiles/version_set_test.dir/util/testharness.cc.o: ext/leveldb/CMakeFiles/version_set_test.dir/flags.make
ext/leveldb/CMakeFiles/version_set_test.dir/util/testharness.cc.o: ../ext/leveldb/util/testharness.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ext/leveldb/CMakeFiles/version_set_test.dir/util/testharness.cc.o"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/version_set_test.dir/util/testharness.cc.o -c /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/util/testharness.cc

ext/leveldb/CMakeFiles/version_set_test.dir/util/testharness.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/version_set_test.dir/util/testharness.cc.i"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/util/testharness.cc > CMakeFiles/version_set_test.dir/util/testharness.cc.i

ext/leveldb/CMakeFiles/version_set_test.dir/util/testharness.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/version_set_test.dir/util/testharness.cc.s"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/util/testharness.cc -o CMakeFiles/version_set_test.dir/util/testharness.cc.s

ext/leveldb/CMakeFiles/version_set_test.dir/util/testutil.cc.o: ext/leveldb/CMakeFiles/version_set_test.dir/flags.make
ext/leveldb/CMakeFiles/version_set_test.dir/util/testutil.cc.o: ../ext/leveldb/util/testutil.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object ext/leveldb/CMakeFiles/version_set_test.dir/util/testutil.cc.o"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/version_set_test.dir/util/testutil.cc.o -c /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/util/testutil.cc

ext/leveldb/CMakeFiles/version_set_test.dir/util/testutil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/version_set_test.dir/util/testutil.cc.i"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/util/testutil.cc > CMakeFiles/version_set_test.dir/util/testutil.cc.i

ext/leveldb/CMakeFiles/version_set_test.dir/util/testutil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/version_set_test.dir/util/testutil.cc.s"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/util/testutil.cc -o CMakeFiles/version_set_test.dir/util/testutil.cc.s

ext/leveldb/CMakeFiles/version_set_test.dir/db/version_set_test.cc.o: ext/leveldb/CMakeFiles/version_set_test.dir/flags.make
ext/leveldb/CMakeFiles/version_set_test.dir/db/version_set_test.cc.o: ../ext/leveldb/db/version_set_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object ext/leveldb/CMakeFiles/version_set_test.dir/db/version_set_test.cc.o"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/version_set_test.dir/db/version_set_test.cc.o -c /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/db/version_set_test.cc

ext/leveldb/CMakeFiles/version_set_test.dir/db/version_set_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/version_set_test.dir/db/version_set_test.cc.i"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/db/version_set_test.cc > CMakeFiles/version_set_test.dir/db/version_set_test.cc.i

ext/leveldb/CMakeFiles/version_set_test.dir/db/version_set_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/version_set_test.dir/db/version_set_test.cc.s"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && /usr/local/Cellar/llvm/7.0.0/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb/db/version_set_test.cc -o CMakeFiles/version_set_test.dir/db/version_set_test.cc.s

# Object files for target version_set_test
version_set_test_OBJECTS = \
"CMakeFiles/version_set_test.dir/util/testharness.cc.o" \
"CMakeFiles/version_set_test.dir/util/testutil.cc.o" \
"CMakeFiles/version_set_test.dir/db/version_set_test.cc.o"

# External object files for target version_set_test
version_set_test_EXTERNAL_OBJECTS =

ext/leveldb/version_set_test: ext/leveldb/CMakeFiles/version_set_test.dir/util/testharness.cc.o
ext/leveldb/version_set_test: ext/leveldb/CMakeFiles/version_set_test.dir/util/testutil.cc.o
ext/leveldb/version_set_test: ext/leveldb/CMakeFiles/version_set_test.dir/db/version_set_test.cc.o
ext/leveldb/version_set_test: ext/leveldb/CMakeFiles/version_set_test.dir/build.make
ext/leveldb/version_set_test: ext/leveldb/libleveldb.a
ext/leveldb/version_set_test: ext/leveldb/CMakeFiles/version_set_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable version_set_test"
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/version_set_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ext/leveldb/CMakeFiles/version_set_test.dir/build: ext/leveldb/version_set_test

.PHONY : ext/leveldb/CMakeFiles/version_set_test.dir/build

ext/leveldb/CMakeFiles/version_set_test.dir/clean:
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb && $(CMAKE_COMMAND) -P CMakeFiles/version_set_test.dir/cmake_clean.cmake
.PHONY : ext/leveldb/CMakeFiles/version_set_test.dir/clean

ext/leveldb/CMakeFiles/version_set_test.dir/depend:
	cd /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/me/Documents/Workspace/GitHub/Cpp/Geologger /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/ext/leveldb /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb /Users/me/Documents/Workspace/GitHub/Cpp/Geologger/cmake-build-debug/ext/leveldb/CMakeFiles/version_set_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ext/leveldb/CMakeFiles/version_set_test.dir/depend

