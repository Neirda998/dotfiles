add_executable(input_test
  option_test.c
  readline_test.c
 )

set_target_properties(input_test PROPERTIES
  C_STANDARD 99
  C_EXTENSIONS OFF
  )
target_link_libraries(input_test PRIVATE
  ${CRITERION_LIB}
  common
  src
 )

target_include_directories(input_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src/
  )

set_target_properties(input_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
