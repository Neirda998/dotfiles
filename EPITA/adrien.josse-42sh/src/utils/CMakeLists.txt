add_library(utils STATIC
  memory.c
  memory.h
  fd_utils.c
  fd_utils.h
  xstring.c
  xstring.h
  )

set_target_properties(utils PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_link_libraries(utils PRIVATE
  common
  input
  )

target_include_directories(utils PRIVATE
  ../utils
  ../input
  ../lexer
  ../parser
  ../free
  ../exec
  ../expand
  )

target_include_directories(utils PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
