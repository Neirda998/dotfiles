add_executable(lexer_test
  split_test.c
  token_test.c
  lexer_test.c
 )


set_target_properties(lexer_test PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_link_libraries(lexer_test PRIVATE
  ${CRITERION_LIB}
  common
  src
 )

target_include_directories(lexer_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )

set_target_properties(lexer_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
