# OPTIMISATION FLAGS : FIXME
# In cmake, we define variables with set(VAR Value [Value]*)
# set(MYVAR "val1") assigns value val1 to MYVAR
# set(MYVAR "val1" "val2") creates a list
set(OPT_FLAGS "-O3")

# END OPTIMIZATION FLAGS
# SOURCES : FIXME

#set(SRC_ENGINE)

include_directories(
  src/chess_engine/ai
  src/chess_engine/board
  src/chess_engine/perft
  src/listener
  src/parsing/option_parser
  src/parsing/perft_parser
  src/parsing/pgn_parser
  src/utils
  tests/chess_engine/ai
  tests/chess_engine/board
  tests/listener
  tests/parsing/option_parser
  tests/parsing/perft_parser
  tests/parsing/pgn_parser
  tests/utils
  )

# END SOURCES

# SETUP
cmake_minimum_required(VERSION 3.12)
project(Chess)

# BUILD OPTIONS
set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g3 -fsanitize=address --coverage -fprofile-arcs -ftest-coverage -DDEBUG")

# LIBRARIES

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost REQUIRED COMPONENTS system program_options)
set(LIBRARIES Boost::system Boost::program_options ${CMAKE_DL_LIBS})

# SRC

add_subdirectory(src)

file(GLOB_RECURSE GCDA_FILES "${PROJECT_BINARY_DIR}/*.gcda")
if(NOT GCDA_FILES STREQUAL "")
  file(REMOVE ${GCDA_FILES})
endif()

# CHESSENGINE
add_executable(chessengine)
target_sources(chessengine PRIVATE ${SRC_ENGINE} ${CMAKE_SOURCE_DIR}/src/main.cc)
target_link_libraries(chessengine PRIVATE src ${LIBRARIES})

# STATIC TARGET
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(chessengine-static)
    target_sources(chessengine-static PRIVATE "src/main.cc")
    target_link_libraries(chessengine-static PRIVATE src ${LIBRARIES} -static)
  endif()

# CLI-LISTENER
add_library(cli-listener EXCLUDE_FROM_ALL SHARED
   ${CMAKE_SOURCE_DIR}/src/listener/cli-listener.cc
   ${CMAKE_SOURCE_DIR}/src/chess_engine/board/utils.cc
   ${CMAKE_SOURCE_DIR}/src/utils/logger.cc)

# TESTS
find_package(GTest)
add_subdirectory(tests)
enable_testing()
if(GTEST_FOUND)
    include(GoogleTest)
    add_test(NAME unit_test COMMAND unit_test)

    add_custom_target(check
        COMMAND env GTEST_COLOR=1 ${CMAKE_CTEST_COMMAND} --verbose
        DEPENDS unit_test
        )
endif()
