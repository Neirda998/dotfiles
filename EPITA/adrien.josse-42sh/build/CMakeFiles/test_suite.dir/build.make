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
CMAKE_SOURCE_DIR = /home/wall/epita/adrien.josse-42sh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wall/epita/adrien.josse-42sh/build

# Utility rule file for test_suite.

# Include the progress variables for this target.
include CMakeFiles/test_suite.dir/progress.make

CMakeFiles/test_suite: 42sh
	bash -c /home/wall/epita/adrien.josse-42sh/tests/python/setup_env.sh

test_suite: CMakeFiles/test_suite
test_suite: CMakeFiles/test_suite.dir/build.make

.PHONY : test_suite

# Rule to build all files generated by this target.
CMakeFiles/test_suite.dir/build: test_suite

.PHONY : CMakeFiles/test_suite.dir/build

CMakeFiles/test_suite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_suite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_suite.dir/clean

CMakeFiles/test_suite.dir/depend:
	cd /home/wall/epita/adrien.josse-42sh/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wall/epita/adrien.josse-42sh /home/wall/epita/adrien.josse-42sh /home/wall/epita/adrien.josse-42sh/build /home/wall/epita/adrien.josse-42sh/build /home/wall/epita/adrien.josse-42sh/build/CMakeFiles/test_suite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_suite.dir/depend
