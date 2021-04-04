add_executable(parser_test
  redirection_test.c
  command_test.c
  compound_list_test.c
  loops_test.c
  if_test.c
  case_test.c
  funcdec_test.c
  simple_command_test.c
  parser_input_test.c
 )


set_target_properties(parser_test PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_link_libraries(parser_test PRIVATE
  ${CRITERION_LIB}
  common
  src
 )

target_include_directories(parser_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )

set_target_properties(parser_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
