# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = "/Users/me/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/181.5540.8/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/me/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/181.5540.8/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NetScanner.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NetScanner.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NetScanner.dir/flags.make

CMakeFiles/NetScanner.dir/main.cpp.o: CMakeFiles/NetScanner.dir/flags.make
CMakeFiles/NetScanner.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NetScanner.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NetScanner.dir/main.cpp.o -c /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/main.cpp

CMakeFiles/NetScanner.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NetScanner.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/main.cpp > CMakeFiles/NetScanner.dir/main.cpp.i

CMakeFiles/NetScanner.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NetScanner.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/main.cpp -o CMakeFiles/NetScanner.dir/main.cpp.s

CMakeFiles/NetScanner.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/NetScanner.dir/main.cpp.o.requires

CMakeFiles/NetScanner.dir/main.cpp.o.provides: CMakeFiles/NetScanner.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/NetScanner.dir/build.make CMakeFiles/NetScanner.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/NetScanner.dir/main.cpp.o.provides

CMakeFiles/NetScanner.dir/main.cpp.o.provides.build: CMakeFiles/NetScanner.dir/main.cpp.o


CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o: CMakeFiles/NetScanner.dir/flags.make
CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o: ../NetScannerLib/netscanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o -c /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/NetScannerLib/netscanner.cpp

CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/NetScannerLib/netscanner.cpp > CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.i

CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/NetScannerLib/netscanner.cpp -o CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.s

CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.requires:

.PHONY : CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.requires

CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.provides: CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.requires
	$(MAKE) -f CMakeFiles/NetScanner.dir/build.make CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.provides.build
.PHONY : CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.provides

CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.provides.build: CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o


# Object files for target NetScanner
NetScanner_OBJECTS = \
"CMakeFiles/NetScanner.dir/main.cpp.o" \
"CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o"

# External object files for target NetScanner
NetScanner_EXTERNAL_OBJECTS =

NetScanner: CMakeFiles/NetScanner.dir/main.cpp.o
NetScanner: CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o
NetScanner: CMakeFiles/NetScanner.dir/build.make
NetScanner: CMakeFiles/NetScanner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable NetScanner"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NetScanner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NetScanner.dir/build: NetScanner

.PHONY : CMakeFiles/NetScanner.dir/build

CMakeFiles/NetScanner.dir/requires: CMakeFiles/NetScanner.dir/main.cpp.o.requires
CMakeFiles/NetScanner.dir/requires: CMakeFiles/NetScanner.dir/NetScannerLib/netscanner.cpp.o.requires

.PHONY : CMakeFiles/NetScanner.dir/requires

CMakeFiles/NetScanner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NetScanner.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NetScanner.dir/clean

CMakeFiles/NetScanner.dir/depend:
	cd /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug /Users/me/Documents/Workspace/GitHub/Cpp/NetScanner/cmake-build-debug/CMakeFiles/NetScanner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NetScanner.dir/depend
