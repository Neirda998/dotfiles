add_library(built-in STATIC
  alias.c
  alias.h
  break.c
  break.h
  built_in_alias.c
  built_in_alias.h
  built_in.c
  built_in.h
  cd.c
  cd.h
  continue.c
  continue.h
  echo.c
  echo.h
  exit.c
  exit.h
  export.c
  export.h
  set.c
  set.h
  source.c
  source.h
  )

target_link_libraries(built-in PRIVATE
  common
  utils
  history
  input
  lexer
  parser
  exec
  )

set_target_properties(built-in PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(built-in PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
