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
include tests/CMakeFiles/unit_test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/unit_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/unit_test.dir/flags.make

tests/CMakeFiles/unit_test.dir/test_main.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/test_main.cc.o: ../tests/test_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/unit_test.dir/test_main.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/test_main.cc.o -c /home/wall/epita/adrien.josse-chess/tests/test_main.cc

tests/CMakeFiles/unit_test.dir/test_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/test_main.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/test_main.cc > CMakeFiles/unit_test.dir/test_main.cc.i

tests/CMakeFiles/unit_test.dir/test_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/test_main.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/test_main.cc -o CMakeFiles/unit_test.dir/test_main.cc.s

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.o: ../tests/chess_engine/board/test_chessboard-representation.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.o -c /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_chessboard-representation.cc

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_chessboard-representation.cc > CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.i

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_chessboard-representation.cc -o CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.s

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.o: ../tests/chess_engine/board/test_chessboard.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.o -c /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_chessboard.cc

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_chessboard.cc > CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.i

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_chessboard.cc -o CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.s

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.o: ../tests/chess_engine/board/test_castling.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tests/CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.o -c /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_castling.cc

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_castling.cc > CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.i

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_castling.cc -o CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.s

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.o: ../tests/chess_engine/board/test_eval.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tests/CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.o -c /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_eval.cc

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_eval.cc > CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.i

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_eval.cc -o CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.s

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.o: ../tests/chess_engine/board/test_legal_moves.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.o -c /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_legal_moves.cc

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_legal_moves.cc > CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.i

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_legal_moves.cc -o CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.s

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.o: ../tests/chess_engine/board/test_legal_crusade.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.o -c /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_legal_crusade.cc

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_legal_crusade.cc > CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.i

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_legal_crusade.cc -o CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.s

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.o: ../tests/chess_engine/board/test_rules.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object tests/CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.o -c /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_rules.cc

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_rules.cc > CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.i

tests/CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/chess_engine/board/test_rules.cc -o CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.s

tests/CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.o: ../tests/parsing/option_parser/test_option_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object tests/CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.o -c /home/wall/epita/adrien.josse-chess/tests/parsing/option_parser/test_option_parser.cc

tests/CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/parsing/option_parser/test_option_parser.cc > CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.i

tests/CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/parsing/option_parser/test_option_parser.cc -o CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.s

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.o: ../tests/parsing/perft_parser/test_fen_object.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.o -c /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_fen_object.cc

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_fen_object.cc > CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.i

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_fen_object.cc -o CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.s

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.o: ../tests/parsing/perft_parser/test_fen_rank.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.o -c /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_fen_rank.cc

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_fen_rank.cc > CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.i

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_fen_rank.cc -o CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.s

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.o: tests/CMakeFiles/unit_test.dir/flags.make
tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.o: ../tests/parsing/perft_parser/test_perft_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.o"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.o -c /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_perft_parser.cc

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.i"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_perft_parser.cc > CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.i

tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.s"
	cd /home/wall/epita/adrien.josse-chess/release/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wall/epita/adrien.josse-chess/tests/parsing/perft_parser/test_perft_parser.cc -o CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.s

# Object files for target unit_test
unit_test_OBJECTS = \
"CMakeFiles/unit_test.dir/test_main.cc.o" \
"CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.o" \
"CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.o" \
"CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.o" \
"CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.o" \
"CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.o" \
"CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.o" \
"CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.o" \
"CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.o" \
"CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.o" \
"CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.o" \
"CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.o"

# External object files for target unit_test
unit_test_EXTERNAL_OBJECTS =

tests/unit_test: tests/CMakeFiles/unit_test.dir/test_main.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard-representation.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/chess_engine/board/test_chessboard.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/chess_engine/board/test_castling.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/chess_engine/board/test_eval.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_moves.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/chess_engine/board/test_legal_crusade.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/chess_engine/board/test_rules.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/parsing/option_parser/test_option_parser.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_object.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_fen_rank.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/parsing/perft_parser/test_perft_parser.cc.o
tests/unit_test: tests/CMakeFiles/unit_test.dir/build.make
tests/unit_test: src/libsrc.a
tests/unit_test: /usr/lib/libgtest.so
tests/unit_test: /usr/lib64/libboost_system.a
tests/unit_test: /usr/lib64/libboost_program_options.a
tests/unit_test: tests/CMakeFiles/unit_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wall/epita/adrien.josse-chess/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable unit_test"
	cd /home/wall/epita/adrien.josse-chess/release/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/unit_test.dir/build: tests/unit_test

.PHONY : tests/CMakeFiles/unit_test.dir/build

tests/CMakeFiles/unit_test.dir/clean:
	cd /home/wall/epita/adrien.josse-chess/release/tests && $(CMAKE_COMMAND) -P CMakeFiles/unit_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/unit_test.dir/clean

tests/CMakeFiles/unit_test.dir/depend:
	cd /home/wall/epita/adrien.josse-chess/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wall/epita/adrien.josse-chess /home/wall/epita/adrien.josse-chess/tests /home/wall/epita/adrien.josse-chess/release /home/wall/epita/adrien.josse-chess/release/tests /home/wall/epita/adrien.josse-chess/release/tests/CMakeFiles/unit_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/unit_test.dir/depend

