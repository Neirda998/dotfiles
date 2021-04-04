add_library(lexer STATIC
  split.c
  split.h
  token.c
  token.h
  lexer.c
  lexer.h
  quote_len.c
  quote_len.h
 )

target_link_libraries(lexer PRIVATE
  common
  input
  utils
  built-in
 )


set_target_properties(lexer PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(lexer PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
