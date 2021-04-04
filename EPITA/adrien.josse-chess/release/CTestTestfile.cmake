# CMake generated Testfile for 
# Source directory: /home/wall/epita/adrien.josse-chess
# Build directory: /home/wall/epita/adrien.josse-chess/release
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit_test "/home/wall/epita/adrien.josse-chess/release/tests/unit_test")
set_tests_properties(unit_test PROPERTIES  _BACKTRACE_TRIPLES "/home/wall/epita/adrien.josse-chess/CMakeLists.txt;89;add_test;/home/wall/epita/adrien.josse-chess/CMakeLists.txt;0;")
subdirs("src")
subdirs("tests")
