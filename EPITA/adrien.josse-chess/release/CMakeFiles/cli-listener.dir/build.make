# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wall/epita/adrien.josse-chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wall/epita/adrien.josse-chess/release

# Include any dependencies generated for this target.
include CMakeFiles/cli-listener.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cli-listener.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cli-listener.dir/flags.make

CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.o: CMakeFiles/cli-listener.dir/flags.make
CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.o: ../src/listener/cli-listener.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.o -c /home/wall/epita/adrien.josse-chess/src/listener/cli-listener.cc

CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/listener/cli-listener.cc > CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.i

CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/listener/cli-listener.cc -o CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.s

CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.o: CMakeFiles/cli-listener.dir/flags.make
CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.o: ../src/chess_engine/board/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/board/utils.cc

CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/board/utils.cc > CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.i

CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/board/utils.cc -o CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.s

CMakeFiles/cli-listener.dir/src/utils/logger.cc.o: CMakeFiles/cli-listener.dir/flags.make
CMakeFiles/cli-listener.dir/src/utils/logger.cc.o: ../src/utils/logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cli-listener.dir/src/utils/logger.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cli-listener.dir/src/utils/logger.cc.o -c /home/wall/epita/adrien.josse-chess/src/utils/logger.cc

CMakeFiles/cli-listener.dir/src/utils/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli-listener.dir/src/utils/logger.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/utils/logger.cc > CMakeFiles/cli-listener.dir/src/utils/logger.cc.i

CMakeFiles/cli-listener.dir/src/utils/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli-listener.dir/src/utils/logger.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/utils/logger.cc -o CMakeFiles/cli-listener.dir/src/utils/logger.cc.s

# Object files for target cli-listener
cli__listener_OBJECTS = \
"CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.o" \
"CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.o" \
"CMakeFiles/cli-listener.dir/src/utils/logger.cc.o"

# External object files for target cli-listener
cli__listener_EXTERNAL_OBJECTS =

libcli-listener.so: CMakeFiles/cli-listener.dir/src/listener/cli-listener.cc.o
libcli-listener.so: CMakeFiles/cli-listener.dir/src/chess_engine/board/utils.cc.o
libcli-listener.so: CMakeFiles/cli-listener.dir/src/utils/logger.cc.o
libcli-listener.so: CMakeFiles/cli-listener.dir/build.make
libcli-listener.so: CMakeFiles/cli-listener.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libcli-listener.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cli-listener.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cli-listener.dir/build: libcli-listener.so

.PHONY : CMakeFiles/cli-listener.dir/build

CMakeFiles/cli-listener.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cli-listener.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cli-listener.dir/clean

CMakeFiles/cli-listener.dir/depend:
	cd /home/wall/epita/adrien.josse-chess/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wall/epita/adrien.josse-chess /home/wall/epita/adrien.josse-chess /home/wall/epita/adrien.josse-chess/release /home/wall/epita/adrien.josse-chess/release /home/wall/epita/adrien.josse-chess/release/CMakeFiles/cli-listener.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cli-listener.dir/depend

