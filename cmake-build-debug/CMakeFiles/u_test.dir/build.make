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
include CMakeFiles/u_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/u_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/u_test.dir/flags.make

CMakeFiles/u_test.dir/tests/test1.cpp.o: CMakeFiles/u_test.dir/flags.make
CMakeFiles/u_test.dir/tests/test1.cpp.o: ../tests/test1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/u_test.dir/tests/test1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/u_test.dir/tests/test1.cpp.o -c /home/danila/source/robots/tests/test1.cpp

CMakeFiles/u_test.dir/tests/test1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/u_test.dir/tests/test1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danila/source/robots/tests/test1.cpp > CMakeFiles/u_test.dir/tests/test1.cpp.i

CMakeFiles/u_test.dir/tests/test1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/u_test.dir/tests/test1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danila/source/robots/tests/test1.cpp -o CMakeFiles/u_test.dir/tests/test1.cpp.s

# Object files for target u_test
u_test_OBJECTS = \
"CMakeFiles/u_test.dir/tests/test1.cpp.o"

# External object files for target u_test
u_test_EXTERNAL_OBJECTS =

u_test: CMakeFiles/u_test.dir/tests/test1.cpp.o
u_test: CMakeFiles/u_test.dir/build.make
u_test: /usr/lib/libgtest.a
u_test: libobstacle.a
u_test: libmap_object.a
u_test: libenvironment_describer.a
u_test: libinterest_point.a
u_test: libobservation_center.a
u_test: libcommand_center.a
u_test: librobot_scout.a
u_test: librobot_commander.a
u_test: libmodule.a
u_test: libpower_generator.a
u_test: libmanaging.a
u_test: libsensor.a
u_test: libdisplay.a
u_test: libmoving_describer.a
u_test: libai_robots.a
u_test: libenergy_consuber.a
u_test: libinterfacelib.a
u_test: libtinyxml2.a
u_test: libobstacle.a
u_test: libmap_object.a
u_test: libenvironment_describer.a
u_test: libobstacle.a
u_test: libmap_object.a
u_test: libenvironment_describer.a
u_test: libmoving_describer.a
u_test: libmodule.a
u_test: CMakeFiles/u_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable u_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/u_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/u_test.dir/build: u_test

.PHONY : CMakeFiles/u_test.dir/build

CMakeFiles/u_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/u_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/u_test.dir/clean

CMakeFiles/u_test.dir/depend:
	cd /home/danila/source/robots/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danila/source/robots /home/danila/source/robots /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug/CMakeFiles/u_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/u_test.dir/depend

