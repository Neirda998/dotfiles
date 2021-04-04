add_library(parser STATIC
  case.c
  case.h
  command.c
  command.h
  compound_list.c
  compound_list.h
  funcdec.c
  funcdec.h
  if.c
  if.h
  loops.c
  loops.h
  parser_input.c
  parser_input.h
  redirection.c
  redirection.h
  simple_command.c
  simple_command.h
  utils.c
  utils.h
 )

target_link_libraries(parser PRIVATE
  common
  lexer
  utils
  free
 )

set_target_properties(parser PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(parser PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
