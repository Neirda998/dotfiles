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

# Include any dependencies generated for this target.
include src/ast/CMakeFiles/ast.dir/depend.make

# Include the progress variables for this target.
include src/ast/CMakeFiles/ast.dir/progress.make

# Include the compile flags for this target's objects.
include src/ast/CMakeFiles/ast.dir/flags.make

src/ast/CMakeFiles/ast.dir/ast_case.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_case.c.o: ../src/ast/ast_case.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/ast/CMakeFiles/ast.dir/ast_case.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_case.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_case.c

src/ast/CMakeFiles/ast.dir/ast_case.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_case.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_case.c > CMakeFiles/ast.dir/ast_case.c.i

src/ast/CMakeFiles/ast.dir/ast_case.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_case.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_case.c -o CMakeFiles/ast.dir/ast_case.c.s

src/ast/CMakeFiles/ast.dir/ast_command.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_command.c.o: ../src/ast/ast_command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/ast/CMakeFiles/ast.dir/ast_command.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_command.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_command.c

src/ast/CMakeFiles/ast.dir/ast_command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_command.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_command.c > CMakeFiles/ast.dir/ast_command.c.i

src/ast/CMakeFiles/ast.dir/ast_command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_command.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_command.c -o CMakeFiles/ast.dir/ast_command.c.s

src/ast/CMakeFiles/ast.dir/ast_compound_list.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_compound_list.c.o: ../src/ast/ast_compound_list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/ast/CMakeFiles/ast.dir/ast_compound_list.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_compound_list.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_compound_list.c

src/ast/CMakeFiles/ast.dir/ast_compound_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_compound_list.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_compound_list.c > CMakeFiles/ast.dir/ast_compound_list.c.i

src/ast/CMakeFiles/ast.dir/ast_compound_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_compound_list.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_compound_list.c -o CMakeFiles/ast.dir/ast_compound_list.c.s

src/ast/CMakeFiles/ast.dir/ast_funcdec.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_funcdec.c.o: ../src/ast/ast_funcdec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/ast/CMakeFiles/ast.dir/ast_funcdec.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_funcdec.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_funcdec.c

src/ast/CMakeFiles/ast.dir/ast_funcdec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_funcdec.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_funcdec.c > CMakeFiles/ast.dir/ast_funcdec.c.i

src/ast/CMakeFiles/ast.dir/ast_funcdec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_funcdec.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_funcdec.c -o CMakeFiles/ast.dir/ast_funcdec.c.s

src/ast/CMakeFiles/ast.dir/ast_if.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_if.c.o: ../src/ast/ast_if.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/ast/CMakeFiles/ast.dir/ast_if.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_if.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_if.c

src/ast/CMakeFiles/ast.dir/ast_if.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_if.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_if.c > CMakeFiles/ast.dir/ast_if.c.i

src/ast/CMakeFiles/ast.dir/ast_if.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_if.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_if.c -o CMakeFiles/ast.dir/ast_if.c.s

src/ast/CMakeFiles/ast.dir/ast_input.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_input.c.o: ../src/ast/ast_input.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/ast/CMakeFiles/ast.dir/ast_input.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_input.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_input.c

src/ast/CMakeFiles/ast.dir/ast_input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_input.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_input.c > CMakeFiles/ast.dir/ast_input.c.i

src/ast/CMakeFiles/ast.dir/ast_input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_input.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_input.c -o CMakeFiles/ast.dir/ast_input.c.s

src/ast/CMakeFiles/ast.dir/ast_loops.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_loops.c.o: ../src/ast/ast_loops.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/ast/CMakeFiles/ast.dir/ast_loops.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_loops.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_loops.c

src/ast/CMakeFiles/ast.dir/ast_loops.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_loops.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_loops.c > CMakeFiles/ast.dir/ast_loops.c.i

src/ast/CMakeFiles/ast.dir/ast_loops.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_loops.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_loops.c -o CMakeFiles/ast.dir/ast_loops.c.s

src/ast/CMakeFiles/ast.dir/ast_redirection.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_redirection.c.o: ../src/ast/ast_redirection.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/ast/CMakeFiles/ast.dir/ast_redirection.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_redirection.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_redirection.c

src/ast/CMakeFiles/ast.dir/ast_redirection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_redirection.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_redirection.c > CMakeFiles/ast.dir/ast_redirection.c.i

src/ast/CMakeFiles/ast.dir/ast_redirection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_redirection.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_redirection.c -o CMakeFiles/ast.dir/ast_redirection.c.s

src/ast/CMakeFiles/ast.dir/ast_utils.c.o: src/ast/CMakeFiles/ast.dir/flags.make
src/ast/CMakeFiles/ast.dir/ast_utils.c.o: ../src/ast/ast_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/ast/CMakeFiles/ast.dir/ast_utils.c.o"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ast.dir/ast_utils.c.o   -c /home/wall/epita/adrien.josse-42sh/src/ast/ast_utils.c

src/ast/CMakeFiles/ast.dir/ast_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ast.dir/ast_utils.c.i"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wall/epita/adrien.josse-42sh/src/ast/ast_utils.c > CMakeFiles/ast.dir/ast_utils.c.i

src/ast/CMakeFiles/ast.dir/ast_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ast.dir/ast_utils.c.s"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wall/epita/adrien.josse-42sh/src/ast/ast_utils.c -o CMakeFiles/ast.dir/ast_utils.c.s

# Object files for target ast
ast_OBJECTS = \
"CMakeFiles/ast.dir/ast_case.c.o" \
"CMakeFiles/ast.dir/ast_command.c.o" \
"CMakeFiles/ast.dir/ast_compound_list.c.o" \
"CMakeFiles/ast.dir/ast_funcdec.c.o" \
"CMakeFiles/ast.dir/ast_if.c.o" \
"CMakeFiles/ast.dir/ast_input.c.o" \
"CMakeFiles/ast.dir/ast_loops.c.o" \
"CMakeFiles/ast.dir/ast_redirection.c.o" \
"CMakeFiles/ast.dir/ast_utils.c.o"

# External object files for target ast
ast_EXTERNAL_OBJECTS =

src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_case.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_command.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_compound_list.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_funcdec.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_if.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_input.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_loops.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_redirection.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/ast_utils.c.o
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/build.make
src/ast/libast.a: src/ast/CMakeFiles/ast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wall/epita/adrien.josse-42sh/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C static library libast.a"
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && $(CMAKE_COMMAND) -P CMakeFiles/ast.dir/cmake_clean_target.cmake
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ast/CMakeFiles/ast.dir/build: src/ast/libast.a

.PHONY : src/ast/CMakeFiles/ast.dir/build

src/ast/CMakeFiles/ast.dir/clean:
	cd /home/wall/epita/adrien.josse-42sh/build/src/ast && $(CMAKE_COMMAND) -P CMakeFiles/ast.dir/cmake_clean.cmake
.PHONY : src/ast/CMakeFiles/ast.dir/clean

src/ast/CMakeFiles/ast.dir/depend:
	cd /home/wall/epita/adrien.josse-42sh/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wall/epita/adrien.josse-42sh /home/wall/epita/adrien.josse-42sh/src/ast /home/wall/epita/adrien.josse-42sh/build /home/wall/epita/adrien.josse-42sh/build/src/ast /home/wall/epita/adrien.josse-42sh/build/src/ast/CMakeFiles/ast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ast/CMakeFiles/ast.dir/depend

