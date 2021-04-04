add_library(ast STATIC
  ast_case.c
  ast_case.h
  ast_command.c
  ast_command.h
  ast_compound_list.c
  ast_compound_list.h
  ast_funcdec.c
  ast_funcdec.h
  ast_if.c
  ast_if.h
  ast_input.c
  ast_input.h
  ast_loops.c
  ast_loops.h
  ast_redirection.c
  ast_redirection.h
  ast_utils.c
  ast_utils.h
  ast_utils.h
  )

target_link_libraries(ast PRIVATE
  common
  utils
  )

set_target_properties(ast PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(ast PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
