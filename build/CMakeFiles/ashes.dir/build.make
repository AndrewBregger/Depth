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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andy/Projects/ashes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andy/Projects/ashes/build

# Include any dependencies generated for this target.
include CMakeFiles/ashes.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ashes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ashes.dir/flags.make

CMakeFiles/ashes.dir/src/main.cpp.o: CMakeFiles/ashes.dir/flags.make
CMakeFiles/ashes.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andy/Projects/ashes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ashes.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ashes.dir/src/main.cpp.o -c /home/andy/Projects/ashes/src/main.cpp

CMakeFiles/ashes.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ashes.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andy/Projects/ashes/src/main.cpp > CMakeFiles/ashes.dir/src/main.cpp.i

CMakeFiles/ashes.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ashes.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andy/Projects/ashes/src/main.cpp -o CMakeFiles/ashes.dir/src/main.cpp.s

# Object files for target ashes
ashes_OBJECTS = \
"CMakeFiles/ashes.dir/src/main.cpp.o"

# External object files for target ashes
ashes_EXTERNAL_OBJECTS =

ashes: CMakeFiles/ashes.dir/src/main.cpp.o
ashes: CMakeFiles/ashes.dir/build.make
ashes: engine/libengine.a
ashes: engine/libGLAD.a
ashes: CMakeFiles/ashes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andy/Projects/ashes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ashes"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ashes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ashes.dir/build: ashes

.PHONY : CMakeFiles/ashes.dir/build

CMakeFiles/ashes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ashes.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ashes.dir/clean

CMakeFiles/ashes.dir/depend:
	cd /home/andy/Projects/ashes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andy/Projects/ashes /home/andy/Projects/ashes /home/andy/Projects/ashes/build /home/andy/Projects/ashes/build /home/andy/Projects/ashes/build/CMakeFiles/ashes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ashes.dir/depend
