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
CMAKE_BINARY_DIR = /home/wall/epita/adrien.josse-chess/debug

# Include any dependencies generated for this target.
include src/CMakeFiles/src.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/src.dir/flags.make

src/CMakeFiles/src.dir/chess_engine/ai/uci.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/ai/uci.cc.o: ../src/chess_engine/ai/uci.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/src.dir/chess_engine/ai/uci.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/ai/uci.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/uci.cc

src/CMakeFiles/src.dir/chess_engine/ai/uci.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/ai/uci.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/uci.cc > CMakeFiles/src.dir/chess_engine/ai/uci.cc.i

src/CMakeFiles/src.dir/chess_engine/ai/uci.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/ai/uci.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/uci.cc -o CMakeFiles/src.dir/chess_engine/ai/uci.cc.s

src/CMakeFiles/src.dir/chess_engine/ai/ai.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/ai/ai.cc.o: ../src/chess_engine/ai/ai.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/src.dir/chess_engine/ai/ai.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/ai/ai.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/ai.cc

src/CMakeFiles/src.dir/chess_engine/ai/ai.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/ai/ai.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/ai.cc > CMakeFiles/src.dir/chess_engine/ai/ai.cc.i

src/CMakeFiles/src.dir/chess_engine/ai/ai.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/ai/ai.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/ai.cc -o CMakeFiles/src.dir/chess_engine/ai/ai.cc.s

src/CMakeFiles/src.dir/chess_engine/ai/minimax.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/ai/minimax.cc.o: ../src/chess_engine/ai/minimax.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/src.dir/chess_engine/ai/minimax.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/ai/minimax.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/minimax.cc

src/CMakeFiles/src.dir/chess_engine/ai/minimax.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/ai/minimax.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/minimax.cc > CMakeFiles/src.dir/chess_engine/ai/minimax.cc.i

src/CMakeFiles/src.dir/chess_engine/ai/minimax.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/ai/minimax.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/ai/minimax.cc -o CMakeFiles/src.dir/chess_engine/ai/minimax.cc.s

src/CMakeFiles/src.dir/chess_engine/board/chessboard.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/board/chessboard.cc.o: ../src/chess_engine/board/chessboard.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/src.dir/chess_engine/board/chessboard.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/board/chessboard.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/board/chessboard.cc

src/CMakeFiles/src.dir/chess_engine/board/chessboard.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/board/chessboard.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/board/chessboard.cc > CMakeFiles/src.dir/chess_engine/board/chessboard.cc.i

src/CMakeFiles/src.dir/chess_engine/board/chessboard.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/board/chessboard.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/board/chessboard.cc -o CMakeFiles/src.dir/chess_engine/board/chessboard.cc.s

src/CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.o: ../src/chess_engine/board/chessboard-representation.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/board/chessboard-representation.cc

src/CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/board/chessboard-representation.cc > CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.i

src/CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/board/chessboard-representation.cc -o CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.s

src/CMakeFiles/src.dir/chess_engine/board/rule.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/board/rule.cc.o: ../src/chess_engine/board/rule.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/src.dir/chess_engine/board/rule.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/board/rule.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/board/rule.cc

src/CMakeFiles/src.dir/chess_engine/board/rule.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/board/rule.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/board/rule.cc > CMakeFiles/src.dir/chess_engine/board/rule.cc.i

src/CMakeFiles/src.dir/chess_engine/board/rule.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/board/rule.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/board/rule.cc -o CMakeFiles/src.dir/chess_engine/board/rule.cc.s

src/CMakeFiles/src.dir/chess_engine/board/utils.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/board/utils.cc.o: ../src/chess_engine/board/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/src.dir/chess_engine/board/utils.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/board/utils.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/board/utils.cc

src/CMakeFiles/src.dir/chess_engine/board/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/board/utils.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/board/utils.cc > CMakeFiles/src.dir/chess_engine/board/utils.cc.i

src/CMakeFiles/src.dir/chess_engine/board/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/board/utils.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/board/utils.cc -o CMakeFiles/src.dir/chess_engine/board/utils.cc.s

src/CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.o: ../src/chess_engine/perft/perft_engine.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.o -c /home/wall/epita/adrien.josse-chess/src/chess_engine/perft/perft_engine.cc

src/CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/chess_engine/perft/perft_engine.cc > CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.i

src/CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/chess_engine/perft/perft_engine.cc -o CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.s

src/CMakeFiles/src.dir/listener/listener_manager.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/listener/listener_manager.cc.o: ../src/listener/listener_manager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/src.dir/listener/listener_manager.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/listener/listener_manager.cc.o -c /home/wall/epita/adrien.josse-chess/src/listener/listener_manager.cc

src/CMakeFiles/src.dir/listener/listener_manager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/listener/listener_manager.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/listener/listener_manager.cc > CMakeFiles/src.dir/listener/listener_manager.cc.i

src/CMakeFiles/src.dir/listener/listener_manager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/listener/listener_manager.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/listener/listener_manager.cc -o CMakeFiles/src.dir/listener/listener_manager.cc.s

src/CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.o: ../src/parsing/option_parser/option_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/option_parser/option_parser.cc

src/CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/option_parser/option_parser.cc > CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.i

src/CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/option_parser/option_parser.cc -o CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.s

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.o: ../src/parsing/pgn_parser/pgn-exception.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-exception.cc

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-exception.cc > CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.i

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-exception.cc -o CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.s

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.o: ../src/parsing/pgn_parser/pgn-move.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-move.cc

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-move.cc > CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.i

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-move.cc -o CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.s

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.o: ../src/parsing/pgn_parser/pgn-parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-parser.cc

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-parser.cc > CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.i

src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/pgn_parser/pgn-parser.cc -o CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.s

src/CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.o: ../src/parsing/perft_parser/fen_rank.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object src/CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/fen_rank.cc

src/CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/fen_rank.cc > CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.i

src/CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/fen_rank.cc -o CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.s

src/CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.o: ../src/parsing/perft_parser/fen_object.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object src/CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/fen_object.cc

src/CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/fen_object.cc > CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.i

src/CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/fen_object.cc -o CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.s

src/CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.o: ../src/parsing/perft_parser/perft_object.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object src/CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/perft_object.cc

src/CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/perft_object.cc > CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.i

src/CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/perft_object.cc -o CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.s

src/CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.o: ../src/parsing/perft_parser/perft_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object src/CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.o -c /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/perft_parser.cc

src/CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/perft_parser.cc > CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.i

src/CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/parsing/perft_parser/perft_parser.cc -o CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.s

src/CMakeFiles/src.dir/utils/logger.cc.o: src/CMakeFiles/src.dir/flags.make
src/CMakeFiles/src.dir/utils/logger.cc.o: ../src/utils/logger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object src/CMakeFiles/src.dir/utils/logger.cc.o"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/src.dir/utils/logger.cc.o -c /home/wall/epita/adrien.josse-chess/src/utils/logger.cc

src/CMakeFiles/src.dir/utils/logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/src.dir/utils/logger.cc.i"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/src/utils/logger.cc > CMakeFiles/src.dir/utils/logger.cc.i

src/CMakeFiles/src.dir/utils/logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/src.dir/utils/logger.cc.s"
	cd /home/wall/epita/adrien.josse-chess/debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/src/utils/logger.cc -o CMakeFiles/src.dir/utils/logger.cc.s

# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/chess_engine/ai/uci.cc.o" \
"CMakeFiles/src.dir/chess_engine/ai/ai.cc.o" \
"CMakeFiles/src.dir/chess_engine/ai/minimax.cc.o" \
"CMakeFiles/src.dir/chess_engine/board/chessboard.cc.o" \
"CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.o" \
"CMakeFiles/src.dir/chess_engine/board/rule.cc.o" \
"CMakeFiles/src.dir/chess_engine/board/utils.cc.o" \
"CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.o" \
"CMakeFiles/src.dir/listener/listener_manager.cc.o" \
"CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.o" \
"CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.o" \
"CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.o" \
"CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.o" \
"CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.o" \
"CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.o" \
"CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.o" \
"CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.o" \
"CMakeFiles/src.dir/utils/logger.cc.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/ai/uci.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/ai/ai.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/ai/minimax.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/board/chessboard.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/board/chessboard-representation.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/board/rule.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/board/utils.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/chess_engine/perft/perft_engine.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/listener/listener_manager.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/option_parser/option_parser.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-exception.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-move.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/pgn_parser/pgn-parser.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/perft_parser/fen_rank.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/perft_parser/fen_object.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/perft_parser/perft_object.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/parsing/perft_parser/perft_parser.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/utils/logger.cc.o
src/libsrc.a: src/CMakeFiles/src.dir/build.make
src/libsrc.a: src/CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wall/epita/adrien.josse-chess/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX static library libsrc.a"
	cd /home/wall/epita/adrien.josse-chess/debug/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	cd /home/wall/epita/adrien.josse-chess/debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/src.dir/build: src/libsrc.a

.PHONY : src/CMakeFiles/src.dir/build

src/CMakeFiles/src.dir/clean:
	cd /home/wall/epita/adrien.josse-chess/debug/src && $(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/src.dir/clean

src/CMakeFiles/src.dir/depend:
	cd /home/wall/epita/adrien.josse-chess/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wall/epita/adrien.josse-chess /home/wall/epita/adrien.josse-chess/src /home/wall/epita/adrien.josse-chess/debug /home/wall/epita/adrien.josse-chess/debug/src /home/wall/epita/adrien.josse-chess/debug/src/CMakeFiles/src.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/src.dir/depend
