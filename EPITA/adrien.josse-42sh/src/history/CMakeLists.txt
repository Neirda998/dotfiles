find_library(READLINE_LIB readline)

add_library(history STATIC
  history.c
  history.h
 )

target_link_libraries(history PRIVATE
  ${READLINE_LIB}
  common
  utils
  )

set_target_properties(history PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(history PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )
