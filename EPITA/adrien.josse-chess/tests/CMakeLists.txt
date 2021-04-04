set(TEST_SOURCES
  test_main.cc
  chess_engine/board/test_chessboard-representation.cc
  chess_engine/board/test_chessboard-representation.cc
  chess_engine/board/test_chessboard.cc
  chess_engine/board/test_castling.cc
  chess_engine/board/test_eval.cc
  chess_engine/board/test_legal_moves.cc
  chess_engine/board/test_legal_crusade.cc
  chess_engine/board/test_rules.cc
  parsing/option_parser/test_option_parser.cc
  parsing/perft_parser/test_fen_object.cc
  parsing/perft_parser/test_fen_rank.cc
  parsing/perft_parser/test_perft_parser.cc
  )

add_executable(unit_test EXCLUDE_FROM_ALL)

target_sources(unit_test PRIVATE
  ${TEST_SOURCES})

target_link_libraries(unit_test PRIVATE
  src
  ${GTEST_LIBRARIES}
  ${LIBRARIES}
  )
