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
include CMakeFiles/robotsCreate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/robotsCreate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robotsCreate.dir/flags.make

CMakeFiles/robotsCreate.dir/main.cpp.o: CMakeFiles/robotsCreate.dir/flags.make
CMakeFiles/robotsCreate.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/robotsCreate.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robotsCreate.dir/main.cpp.o -c /home/danila/source/robots/main.cpp

CMakeFiles/robotsCreate.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robotsCreate.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danila/source/robots/main.cpp > CMakeFiles/robotsCreate.dir/main.cpp.i

CMakeFiles/robotsCreate.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robotsCreate.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danila/source/robots/main.cpp -o CMakeFiles/robotsCreate.dir/main.cpp.s

# Object files for target robotsCreate
robotsCreate_OBJECTS = \
"CMakeFiles/robotsCreate.dir/main.cpp.o"

# External object files for target robotsCreate
robotsCreate_EXTERNAL_OBJECTS =

robotsCreate: CMakeFiles/robotsCreate.dir/main.cpp.o
robotsCreate: CMakeFiles/robotsCreate.dir/build.make
robotsCreate: libinterfacelib.a
robotsCreate: libobstacle.a
robotsCreate: libtinyxml2.a
robotsCreate: libmap_object.a
robotsCreate: libenvironment_describer.a
robotsCreate: libinterest_point.a
robotsCreate: libobservation_center.a
robotsCreate: libcommand_center.a
robotsCreate: librobot_scout.a
robotsCreate: librobot_commander.a
robotsCreate: libmodule.a
robotsCreate: libpower_generator.a
robotsCreate: libmanaging.a
robotsCreate: libsensor.a
robotsCreate: libdisplay.a
robotsCreate: libmoving_describer.a
robotsCreate: libai_robots.a
robotsCreate: libenergy_consuber.a
robotsCreate: /home/danila/source/libraries/SFML-2.5.1/lib/libsfml-graphics.so.2.5.1
robotsCreate: /home/danila/source/libraries/SFML-2.5.1/lib/libsfml-window.so.2.5.1
robotsCreate: /home/danila/source/libraries/SFML-2.5.1/lib/libsfml-audio.so.2.5.1
robotsCreate: libobstacle.a
robotsCreate: libmap_object.a
robotsCreate: libenvironment_describer.a
robotsCreate: libobstacle.a
robotsCreate: libmap_object.a
robotsCreate: libenvironment_describer.a
robotsCreate: libmodule.a
robotsCreate: libmoving_describer.a
robotsCreate: /home/danila/source/libraries/SFML-2.5.1/lib/libsfml-system.so.2.5.1
robotsCreate: CMakeFiles/robotsCreate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable robotsCreate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robotsCreate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robotsCreate.dir/build: robotsCreate

.PHONY : CMakeFiles/robotsCreate.dir/build

CMakeFiles/robotsCreate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/robotsCreate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/robotsCreate.dir/clean

CMakeFiles/robotsCreate.dir/depend:
	cd /home/danila/source/robots/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danila/source/robots /home/danila/source/robots /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug/CMakeFiles/robotsCreate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robotsCreate.dir/depend

