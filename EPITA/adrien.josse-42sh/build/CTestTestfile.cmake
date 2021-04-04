# CMake generated Testfile for 
# Source directory: /home/wall/epita/adrien.josse-42sh
# Build directory: /home/wall/epita/adrien.josse-42sh/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(input_test "/home/wall/epita/adrien.josse-42sh/build/tests/input/input_test")
set_tests_properties(input_test PROPERTIES  _BACKTRACE_TRIPLES "/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;59;add_test;/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;0;")
add_test(lexer_test "/home/wall/epita/adrien.josse-42sh/build/tests/lexer/lexer_test")
set_tests_properties(lexer_test PROPERTIES  _BACKTRACE_TRIPLES "/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;60;add_test;/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;0;")
add_test(parser_test "/home/wall/epita/adrien.josse-42sh/build/tests/parser/parser_test")
set_tests_properties(parser_test PROPERTIES  _BACKTRACE_TRIPLES "/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;61;add_test;/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;0;")
add_test(expand_test "/home/wall/epita/adrien.josse-42sh/build/tests/expand/expand_test")
set_tests_properties(expand_test PROPERTIES  _BACKTRACE_TRIPLES "/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;62;add_test;/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;0;")
add_test(exec_test "/home/wall/epita/adrien.josse-42sh/build/tests/exec/exec_test")
set_tests_properties(exec_test PROPERTIES  _BACKTRACE_TRIPLES "/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;63;add_test;/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;0;")
add_test(test_suite "python3" "/home/wall/epita/adrien.josse-42sh/tests/python/test_suite.py" "./42sh")
set_tests_properties(test_suite PROPERTIES  _BACKTRACE_TRIPLES "/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;64;add_test;/home/wall/epita/adrien.josse-42sh/CMakeLists.txt;0;")
subdirs("src")
subdirs("tests")
