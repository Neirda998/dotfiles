add_library(free STATIC
  case_free.c
  case_free.h
  command_free.c
  command_free.h
  compound_list_free.c
  compound_list_free.h
  funcdec_free.c
  funcdec_free.h
  if_free.c
  if_free.h
  loops_free.c
  loops_free.h
  parser_input_free.c
  parser_input_free.h
  redirection_free.c
  redirection_free.h
  simple_command_free.c
  simple_command_free.h
 )

target_link_libraries(free PRIVATE
  common
  parser
 )

set_target_properties(free PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(free PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
