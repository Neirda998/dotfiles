add_executable(exec_test
  exec_simple_command_test.c
 )

target_link_libraries(exec_test PRIVATE
  ${CRITERION_LIB}
  common
  src
  )

set_target_properties(exec_test PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_include_directories(exec_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )

set_target_properties(exec_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
