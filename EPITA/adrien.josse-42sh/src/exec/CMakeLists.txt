add_library(exec STATIC
  exec_case.c
  exec_case.h
  exec_command.c
  exec_command.h
  exec_compound_list.c
  exec_compound_list.h
  exec_funcdec.c
  exec_funcdec.h
  exec_if.c
  exec_if.h
  exec_input.c
  exec_input.h
  exec_loops.c
  exec_loops.h
  exec_redirection.c
  exec_redirection_bis.c
  exec_redirection.h
  exec_simple_command.c
  exec_simple_command.h
  main_utils.c
  main_utils.h
 )

target_link_libraries(exec PRIVATE
  common
  ast
  utils
  expand
  built-in
  )

set_target_properties(exec PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(exec PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
