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
include CMakeFiles/robot_commander.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/robot_commander.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robot_commander.dir/flags.make

CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.o: CMakeFiles/robot_commander.dir/flags.make
CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.o: ../robots/Robot_Commander.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.o -c /home/danila/source/robots/robots/Robot_Commander.cpp

CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danila/source/robots/robots/Robot_Commander.cpp > CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.i

CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danila/source/robots/robots/Robot_Commander.cpp -o CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.s

# Object files for target robot_commander
robot_commander_OBJECTS = \
"CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.o"

# External object files for target robot_commander
robot_commander_EXTERNAL_OBJECTS =

librobot_commander.a: CMakeFiles/robot_commander.dir/robots/Robot_Commander.cpp.o
librobot_commander.a: CMakeFiles/robot_commander.dir/build.make
librobot_commander.a: CMakeFiles/robot_commander.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librobot_commander.a"
	$(CMAKE_COMMAND) -P CMakeFiles/robot_commander.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robot_commander.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robot_commander.dir/build: librobot_commander.a

.PHONY : CMakeFiles/robot_commander.dir/build

CMakeFiles/robot_commander.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/robot_commander.dir/cmake_clean.cmake
.PHONY : CMakeFiles/robot_commander.dir/clean

CMakeFiles/robot_commander.dir/depend:
	cd /home/danila/source/robots/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danila/source/robots /home/danila/source/robots /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug/CMakeFiles/robot_commander.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robot_commander.dir/depend

