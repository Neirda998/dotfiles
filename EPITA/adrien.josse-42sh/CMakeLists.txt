cmake_minimum_required(VERSION 3.0)

project(42sh VERSION 0.0.1 LANGUAGES C)

add_library(common INTERFACE)

target_compile_options(common INTERFACE
  "-Wall"
  "-Wextra"
  "-pedantic"
  "-Werror"
  "-fsanitize=address"
  "-g"
 )

target_compile_definitions(common INTERFACE
  _POSIX_C_SOURCE=200809L
  _GNU_SOURCE=1
  )
target_link_libraries(common INTERFACE
  $<$<NOT:$<CONFIG:Release>>: -fsanitize=address>
 )

find_library(CRITERION_LIB criterion)
find_library(READLINE_LIB readline)

if (NOT READLINE_LIB)
  MESSAGE(FATAL_ERRORO "Could not find READLINE_LIB.")
endif()

add_subdirectory(src)
add_subdirectory(tests)

add_executable(42sh
  src/42sh.c
 )

target_compile_definitions(42sh PRIVATE
  _POSIX_C_SOURCE=200809L
  )

target_link_libraries(42sh PRIVATE
  common
  src
  )

set_target_properties(42sh PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(42sh PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )

enable_testing()

if(CRITERION_LIB)
  add_test(NAME input_test COMMAND input_test)
  add_test(NAME lexer_test COMMAND lexer_test)
  add_test(NAME parser_test COMMAND parser_test)
  add_test(NAME expand_test COMMAND expand_test)
  add_test(NAME exec_test COMMAND exec_test)
  add_test(NAME test_suite
    COMMAND python3 "${CMAKE_SOURCE_DIR}/tests/python/test_suite.py" ./42sh)
endif()

add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} --verbose
  DEPENDS input_test lexer_test parser_test expand_test exec_test)
add_custom_target(doc
  COMMAND doxygen ${CMAKE_SOURCE_DIR}/doc/Doxyfile
  COMMAND firefox -new-window ${CMAKE_SOURCE_DIR}/doc/html/index.html)
add_custom_target(test_suite
  COMMAND bash -c "${CMAKE_SOURCE_DIR}/tests/python/setup_env.sh"
  DEPENDS 42sh)
