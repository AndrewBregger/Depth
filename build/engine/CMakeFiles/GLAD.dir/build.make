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
include engine/CMakeFiles/GLAD.dir/depend.make

# Include the progress variables for this target.
include engine/CMakeFiles/GLAD.dir/progress.make

# Include the compile flags for this target's objects.
include engine/CMakeFiles/GLAD.dir/flags.make

engine/CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.o: engine/CMakeFiles/GLAD.dir/flags.make
engine/CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.o: ../external/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andy/Projects/ashes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object engine/CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.o"
	cd /home/andy/Projects/ashes/build/engine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.o   -c /home/andy/Projects/ashes/external/glad/src/glad.c

engine/CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.i"
	cd /home/andy/Projects/ashes/build/engine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andy/Projects/ashes/external/glad/src/glad.c > CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.i

engine/CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.s"
	cd /home/andy/Projects/ashes/build/engine && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andy/Projects/ashes/external/glad/src/glad.c -o CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.s

# Object files for target GLAD
GLAD_OBJECTS = \
"CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.o"

# External object files for target GLAD
GLAD_EXTERNAL_OBJECTS =

engine/libGLAD.a: engine/CMakeFiles/GLAD.dir/__/external/glad/src/glad.c.o
engine/libGLAD.a: engine/CMakeFiles/GLAD.dir/build.make
engine/libGLAD.a: engine/CMakeFiles/GLAD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andy/Projects/ashes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libGLAD.a"
	cd /home/andy/Projects/ashes/build/engine && $(CMAKE_COMMAND) -P CMakeFiles/GLAD.dir/cmake_clean_target.cmake
	cd /home/andy/Projects/ashes/build/engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GLAD.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
engine/CMakeFiles/GLAD.dir/build: engine/libGLAD.a

.PHONY : engine/CMakeFiles/GLAD.dir/build

engine/CMakeFiles/GLAD.dir/clean:
	cd /home/andy/Projects/ashes/build/engine && $(CMAKE_COMMAND) -P CMakeFiles/GLAD.dir/cmake_clean.cmake
.PHONY : engine/CMakeFiles/GLAD.dir/clean

engine/CMakeFiles/GLAD.dir/depend:
	cd /home/andy/Projects/ashes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andy/Projects/ashes /home/andy/Projects/ashes/engine /home/andy/Projects/ashes/build /home/andy/Projects/ashes/build/engine /home/andy/Projects/ashes/build/engine/CMakeFiles/GLAD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : engine/CMakeFiles/GLAD.dir/depend

