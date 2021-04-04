find_library(READLINE_LIB readline)

add_library(input STATIC
  env.c
  env.h
  input.c
  input.h
  option.c
  option.h
  readline.c
  readline.h
  )

set_target_properties(input PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_link_libraries(input PRIVATE
  ${READLINE_LIB}
  common
  utils
  history
  )

target_include_directories(input PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
