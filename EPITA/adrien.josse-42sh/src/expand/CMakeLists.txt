add_library(expand STATIC
  expand.c
  expand.h
  expand_arithmetic.c
  expand_arithmetic.h
  expand_arithmetic_exec.c
  expand_arithmetic_exec.h
  expand_arithmetic_free.c
  expand_arithmetic_free.h
  expand_arithmetic_free_2.c
  expand_arithmetic_free_2.h
  expand_arithmetic_lexer.c
  expand_arithmetic_lexer.h
  expand_arithmetic_parser.c
  expand_arithmetic_parser.h
  expand_command.c
  expand_command.h
  expand_tildes.c
  expand_tildes.h
  expand_utils.c
  expand_utils.h
  expand_tildes.c
  expand_tildes.h
  expand_parameters.c
  expand_parameters.h
  expand_path.c
  expand_path.h
  variables.c
  variables.h
  )

target_link_libraries(expand PRIVATE
  common
  utils
  input
  exec
  )

set_target_properties(expand PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(expand PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
