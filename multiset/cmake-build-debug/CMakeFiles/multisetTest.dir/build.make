# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/danila/source/bins/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/danila/source/bins/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/danila/source/robots/multiset

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danila/source/robots/multiset/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/multisetTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multisetTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multisetTest.dir/flags.make

CMakeFiles/multisetTest.dir/main.cpp.o: CMakeFiles/multisetTest.dir/flags.make
CMakeFiles/multisetTest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danila/source/robots/multiset/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multisetTest.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multisetTest.dir/main.cpp.o -c /home/danila/source/robots/multiset/main.cpp

CMakeFiles/multisetTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multisetTest.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danila/source/robots/multiset/main.cpp > CMakeFiles/multisetTest.dir/main.cpp.i

CMakeFiles/multisetTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multisetTest.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danila/source/robots/multiset/main.cpp -o CMakeFiles/multisetTest.dir/main.cpp.s

# Object files for target multisetTest
multisetTest_OBJECTS = \
"CMakeFiles/multisetTest.dir/main.cpp.o"

# External object files for target multisetTest
multisetTest_EXTERNAL_OBJECTS =

multisetTest: CMakeFiles/multisetTest.dir/main.cpp.o
multisetTest: CMakeFiles/multisetTest.dir/build.make
multisetTest: CMakeFiles/multisetTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danila/source/robots/multiset/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable multisetTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multisetTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multisetTest.dir/build: multisetTest

.PHONY : CMakeFiles/multisetTest.dir/build

CMakeFiles/multisetTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multisetTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multisetTest.dir/clean

CMakeFiles/multisetTest.dir/depend:
	cd /home/danila/source/robots/multiset/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danila/source/robots/multiset /home/danila/source/robots/multiset /home/danila/source/robots/multiset/cmake-build-debug /home/danila/source/robots/multiset/cmake-build-debug /home/danila/source/robots/multiset/cmake-build-debug/CMakeFiles/multisetTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multisetTest.dir/depend
