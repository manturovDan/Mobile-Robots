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
include CMakeFiles/energy_consuber.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/energy_consuber.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/energy_consuber.dir/flags.make

CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.o: CMakeFiles/energy_consuber.dir/flags.make
CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.o: ../robots/Energy_Consumer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.o -c /home/danila/source/robots/robots/Energy_Consumer.cpp

CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/danila/source/robots/robots/Energy_Consumer.cpp > CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.i

CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/danila/source/robots/robots/Energy_Consumer.cpp -o CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.s

# Object files for target energy_consuber
energy_consuber_OBJECTS = \
"CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.o"

# External object files for target energy_consuber
energy_consuber_EXTERNAL_OBJECTS =

libenergy_consuber.a: CMakeFiles/energy_consuber.dir/robots/Energy_Consumer.cpp.o
libenergy_consuber.a: CMakeFiles/energy_consuber.dir/build.make
libenergy_consuber.a: CMakeFiles/energy_consuber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danila/source/robots/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libenergy_consuber.a"
	$(CMAKE_COMMAND) -P CMakeFiles/energy_consuber.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/energy_consuber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/energy_consuber.dir/build: libenergy_consuber.a

.PHONY : CMakeFiles/energy_consuber.dir/build

CMakeFiles/energy_consuber.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/energy_consuber.dir/cmake_clean.cmake
.PHONY : CMakeFiles/energy_consuber.dir/clean

CMakeFiles/energy_consuber.dir/depend:
	cd /home/danila/source/robots/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danila/source/robots /home/danila/source/robots /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug /home/danila/source/robots/cmake-build-debug/CMakeFiles/energy_consuber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/energy_consuber.dir/depend

