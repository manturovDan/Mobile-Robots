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
CMAKE_SOURCE_DIR = /home/danila/source/robots

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danila/source/robots/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/robot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/robot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robot.dir/flags.make

CMakeFiles/robot.dir/robots/environment.cpp.o: CMakeFiles/robot.dir/flags.make
CMakeFiles/robot.dir/robots/environment.cpp.o: ../robots/environment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/robot.dir/robots/environment.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robot.dir/robots/environment.cpp.o -c /home/danila/source/robots/robots/environment.cpp

CMakeFiles/robot.dir/robots/environment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot.dir/robots/environment.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danila/source/robots/robots/environment.cpp > CMakeFiles/robot.dir/robots/environment.cpp.i

CMakeFiles/robot.dir/robots/environment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot.dir/robots/environment.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danila/source/robots/robots/environment.cpp -o CMakeFiles/robot.dir/robots/environment.cpp.s

# Object files for target robot
robot_OBJECTS = \
"CMakeFiles/robot.dir/robots/environment.cpp.o"

# External object files for target robot
robot_EXTERNAL_OBJECTS =

librobot.a: CMakeFiles/robot.dir/robots/environment.cpp.o
librobot.a: CMakeFiles/robot.dir/build.make
librobot.a: CMakeFiles/robot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librobot.a"
	$(CMAKE_COMMAND) -P CMakeFiles/robot.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robot.dir/build: librobot.a

.PHONY : CMakeFiles/robot.dir/build

CMakeFiles/robot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/robot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/robot.dir/clean

CMakeFiles/robot.dir/depend:
	cd /home/danila/source/robots/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danila/source/robots /home/danila/source/robots /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug/CMakeFiles/robot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robot.dir/depend

