add_library(src INTERFACE)

target_link_libraries(src INTERFACE
  common
  utils
  input
  lexer
  parser
  ast
  expand
  free
  exec
  history
  built-in
  )

target_include_directories(src INTERFACE)

add_subdirectory(utils)
add_subdirectory(input)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(ast)
add_subdirectory(expand)
add_subdirectory(free)
add_subdirectory(exec)
add_subdirectory(history)
add_subdirectory(built-in)
