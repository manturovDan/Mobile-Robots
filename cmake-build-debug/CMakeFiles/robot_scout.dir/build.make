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
include CMakeFiles/robot_scout.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/robot_scout.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robot_scout.dir/flags.make

CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.o: CMakeFiles/robot_scout.dir/flags.make
CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.o: ../robots/Robot_Scout.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.o -c /home/danila/source/robots/robots/Robot_Scout.cpp

CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danila/source/robots/robots/Robot_Scout.cpp > CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.i

CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danila/source/robots/robots/Robot_Scout.cpp -o CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.s

# Object files for target robot_scout
robot_scout_OBJECTS = \
"CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.o"

# External object files for target robot_scout
robot_scout_EXTERNAL_OBJECTS =

librobot_scout.a: CMakeFiles/robot_scout.dir/robots/Robot_Scout.cpp.o
librobot_scout.a: CMakeFiles/robot_scout.dir/build.make
librobot_scout.a: CMakeFiles/robot_scout.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library librobot_scout.a"
	$(CMAKE_COMMAND) -P CMakeFiles/robot_scout.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robot_scout.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robot_scout.dir/build: librobot_scout.a

.PHONY : CMakeFiles/robot_scout.dir/build

CMakeFiles/robot_scout.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/robot_scout.dir/cmake_clean.cmake
.PHONY : CMakeFiles/robot_scout.dir/clean

CMakeFiles/robot_scout.dir/depend:
	cd /home/danila/source/robots/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danila/source/robots /home/danila/source/robots /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug/CMakeFiles/robot_scout.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robot_scout.dir/depend

