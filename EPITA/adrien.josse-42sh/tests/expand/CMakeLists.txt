add_executable(expand_test
  expand_parameters_test.c
  expand_utils_test.c
  expand_tildes_test.c
  variables_test.c
 )

set_target_properties(expand_test PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )

target_link_libraries(expand_test PRIVATE
  ${CRITERION_LIB}
  common
  src
 )

target_include_directories(expand_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )

set_target_properties(expand_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
