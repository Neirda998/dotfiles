#include <iostream>

#include "chessboard.hh"
#include "move.hh"
#include "rule.hh"
#include "utils.hh"

namespace board {
    static std::vector<std::pair<int, int>>
    get_coordinates_list(std::vector<uint64_t> board_list) {
        std::vector<std::pair<int, int>> empty;
        std::vector<std::pair<int, int>> res;
        for (uint64_t board : board_list) {
            auto coords = get_coordinates(board);
            if (coords.first == -1)
                return empty;
            res.push_back(coords);
        }
        return res;
    }

    static void add_capture_move(std::vector<Move>& moves, uint64_t src,
        PieceType piece, const Chessboard& board, int file, int rank,
        const std::optional<PieceType>& promotion, bool en_passant)
    {
        int rank_d = board.white_turn_get() ? -1 : 1;
        if (en_passant && pos_to_int(file, rank + rank_d)
            == board.en_passant_get())
        {
            //int idx_en_passant =
            //   board.rep_get().get_sqr_piece(file, rank + rank_d);
            //if (idx_en_passant == (board.white_turn_get() * 6 + 4))
            //{
            moves.emplace(moves.begin(), src, pos_to_int(file, rank),
                    PieceType::PAWN, std::nullopt, PieceType::PAWN,
                    false, false, false, true);
            //}
            return;
        }

        if (!en_passant)
        {
            int idx = board.rep_get().get_sqr_piece(file, rank);
            if (idx >= (board.white_turn_get() * 6)
                && idx <= (board.white_turn_get() * 6 + 5))
            {
                moves.emplace(moves.begin(), src, pos_to_int(file, rank),
                    piece, promotion, piecetype_array[idx % 6],
                    false, false, false, false);
            }
        }
    }

    static bool is_occupied(const Chessboard& board, int file, int rank)
    {
        return board.rep_get().get_sqr_piece(file, rank) != 12;
    }

    std::vector<Move> Rule::generate_all_moves(const Chessboard& board)
    {
        auto moves = std::vector<Move>();

        auto append_moves = generate_pawn_moves(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_queen_moves(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_knight_moves(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_bishop_moves(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_rook_moves(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_king_moves(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        return moves;
    }

    std::vector<Move> Rule::generate_all_captures(const Chessboard& board)
    {
        auto moves = std::vector<Move>();

        auto append_moves = generate_pawn_captures(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_queen_captures(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_knight_captures(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_bishop_captures(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_rook_captures(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        append_moves = generate_king_captures(board);
        moves.insert(
            moves.end(),
            std::make_move_iterator(append_moves.begin()),
            std::make_move_iterator(append_moves.end())
        );

        return moves;
    }


    std::vector<Move> Rule::generate_pawn_moves(const Chessboard& board)
    {
        std::vector<Move> moves;

        int rank_d = board.white_turn_get() ? 1 : -1;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(!board.white_turn_get() * 6 + 4);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            if (((board.white_turn_get() && rank == 1)
                 || (!board.white_turn_get() && rank == 6))
                && !is_occupied(board, file, rank + rank_d)
                && !is_occupied(board, file, rank + 2 * rank_d))
            { //Double Pawn Push
                moves.emplace_back(src_boards[i],
                                   pos_to_int(file, rank + 2 * rank_d),
                PieceType::PAWN, std::nullopt, std::nullopt,
                true, false, false, false);
            }
            if (((board.white_turn_get() && rank == 4)
                 || (!board.white_turn_get() && rank == 3)))
            { // Prise en passant
                if (file > 0) { // Left capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file - 1, rank + rank_d, std::nullopt, true);
                }
                if (file < 7) { // Right capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file + 1, rank + rank_d, std::nullopt, true);
                }
            }
            if ((board.white_turn_get() && rank < 6)
                || (!board.white_turn_get() && rank > 1))
            { // Forward
                if (!is_occupied(board, file, rank + rank_d))
                {
                    moves.emplace_back(src_boards[i],
                                       pos_to_int(file, rank + rank_d),
                    PieceType::PAWN, std::nullopt, std::nullopt,
                    false, false, false, false);
                }

                if (file > 0)
                { // Left capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file - 1, rank + rank_d, std::nullopt, false);
                }
                if (file < 7) { // Right capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file + 1, rank + rank_d, std::nullopt, false);
                }
            }
            else if ((board.white_turn_get() && rank < 7)
                     || (!board.white_turn_get() && rank > 0))
            { // Pawn Promotion
                for (size_t k = 0; k < 4; k++)
                {
                    if (!is_occupied(board, file, rank + rank_d))
                    {
                        moves.emplace_back(src_boards[i],
                                           pos_to_int(file, rank + rank_d),
                        PieceType::PAWN, piecetype_array[k], std::nullopt,
                        false, false, false, false);
                    }

                    if (file > 0)
                    { // Left capture
                        add_capture_move(moves, src_boards[i], PieceType::PAWN,
                                         board, file - 1, rank + rank_d,
                                         piecetype_array[k], false);
                    }
                    if (file < 7)
                    { // Right capture
                        add_capture_move(moves, src_boards[i],
                                         PieceType::PAWN, board, file + 1,
                                         rank + rank_d, piecetype_array[k],
                                         false);
                    }
                }
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_pawn_captures(const Chessboard& board)
    {
        std::vector<Move> moves;

        int rank_d = board.white_turn_get() ? 1 : -1;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(!board.white_turn_get() * 6 + 4);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            if (((board.white_turn_get() && rank == 4)
                 || (!board.white_turn_get() && rank == 3)))
            { // Prise en passant
                if (file > 0) { // Left capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file - 1, rank + rank_d, std::nullopt, true);
                }
                if (file < 7) { // Right capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file + 1, rank + rank_d, std::nullopt, true);
                }
            }
            if ((board.white_turn_get() && rank < 6)
                || (!board.white_turn_get() && rank > 1))
            {
                if (file > 0)
                { // Left capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file - 1, rank + rank_d, std::nullopt, false);
                }
                if (file < 7) { // Right capture
                    add_capture_move(moves, src_boards[i], PieceType::PAWN,
                    board, file + 1, rank + rank_d, std::nullopt, false);
                }
            }
            else if ((board.white_turn_get() && rank < 7)
                     || (!board.white_turn_get() && rank > 0))
            { // Pawn Promotion
                for (size_t k = 0; k < 4; k++)
                {
                    if (file > 0)
                    { // Left capture
                        add_capture_move(moves, src_boards[i], PieceType::PAWN,
                                         board, file - 1, rank + rank_d,
                                         piecetype_array[k], false);
                    }
                    if (file < 7)
                    { // Right capture
                        add_capture_move(moves, src_boards[i],
                                         PieceType::PAWN, board, file + 1,
                                         rank + rank_d, piecetype_array[k],
                                         false);
                    }
                }
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_king_moves(const Chessboard& board) {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(5 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            if (file > 0)
            {
                if (!is_occupied(board, file - 1, rank))
                {
                    moves.emplace_back(src_boards[i],
                                       pos_to_int(file - 1, rank),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt,
                                       false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                    board, file - 1, rank, std::nullopt, false);
            }
            if (rank > 0)
            {
                if (!is_occupied(board, file, rank - 1))
                {
                    moves.emplace_back(src_boards[i],
                                       pos_to_int(file, rank - 1),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file, rank - 1, std::nullopt, false);
            }
            if (file > 0 && rank > 0)
            {
                if (!is_occupied(board, file - 1, rank - 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file - 1,
                                                                 rank - 1),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file - 1, rank - 1, std::nullopt,
                                 false);
            }
            if (file < 7)
            {
                if (!is_occupied(board, file + 1, rank))
                {
                    moves.emplace_back(src_boards[i],
                                       pos_to_int(file + 1, rank),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file + 1, rank, std::nullopt, false);
            }
            if (file < 7 && rank > 0)
            {
                if (!is_occupied(board, file + 1, rank - 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file + 1,
                                                                 rank - 1),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file + 1, rank - 1, std::nullopt,
                                 false);
            }
            if (rank < 7)
            {
                if (!is_occupied(board, file, rank + 1))
                {
                    moves.emplace_back(src_boards[i],
                                       pos_to_int(file, rank + 1),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file, rank + 1, std::nullopt, false);
            }
            if (file > 0 && rank < 7)
            {
                if (!is_occupied(board, file - 1, rank + 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file - 1,
                                                                 rank + 1),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file - 1, rank + 1, std::nullopt,
                                 false);
            }
            if (rank < 7 && file < 7)
            {
                if (!is_occupied(board, file + 1, rank + 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file + 1,
                                                                 rank + 1),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file + 1, rank + 1, std::nullopt,
                                 false);
            }

            if (board.white_turn_get())
            {
                if (board.white_king_castling_get()
                        && !is_occupied(board, file + 2, rank)
                        && !is_occupied(board, file + 1, rank))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file + 2,
                                                                 rank),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, true,
                                       false, false);
                }
                if (board.white_queen_castling_get()
                        && !is_occupied(board, file - 2, rank)
                        && !is_occupied(board, file - 1, rank))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file - 2,
                                                                 rank),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false,
                                       true, false);
                }
            }
            else
            {
                if (board.black_king_castling_get()
                        && !is_occupied(board, file + 2, rank)
                        && !is_occupied(board, file + 1, rank))
                {
                    moves.emplace_back(src_boards[i],
                                       pos_to_int(file + 2, rank),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, true,
                                       false, false);
                }
                if (board.black_queen_castling_get()
                        && !is_occupied(board, file - 2, rank)
                        && !is_occupied(board, file - 1, rank))
                {
                    moves.emplace_back(src_boards[i],
                                       pos_to_int(file - 2, rank),
                                       PieceType::KING, std::nullopt,
                                       std::nullopt, false, false,
                                       true, false);
                }
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_king_captures(const Chessboard& board) {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(5 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            if (file > 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                    board, file - 1, rank, std::nullopt, false);
            }
            if (rank > 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file, rank - 1, std::nullopt, false);
            }
            if (file > 0 && rank > 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file - 1, rank - 1, std::nullopt,
                                 false);
            }
            if (file < 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file + 1, rank, std::nullopt, false);
            }
            if (file < 7 && rank > 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file + 1, rank - 1, std::nullopt,
                                 false);
            }
            if (rank < 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file, rank + 1, std::nullopt, false);
            }
            if (file > 0 && rank < 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file - 1, rank + 1, std::nullopt,
                                 false);
            }
            if (rank < 7 && file < 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::KING,
                                 board, file + 1, rank + 1, std::nullopt,
                                 false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_knight_moves(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(3 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            if (file - 1 >= 0 && rank + 2 <= 7)
            {
                if (!is_occupied(board, file - 1, rank + 2))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file - 1,
                                                                 rank + 2),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 1, rank + 2, std::nullopt,
                                 false);
            }

            if (file + 1 <= 7 && rank + 2 <= 7)
            {
                if (!is_occupied(board, file + 1, rank + 2))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file + 1,
                                                                 rank + 2),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 1, rank + 2, std::nullopt,
                                 false);
            }

            if (file + 2 <= 7 && rank + 1 <= 7)
            {
                if (!is_occupied(board, file + 2, rank + 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file + 2,
                                                                 rank + 1),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 2, rank + 1, std::nullopt,
                                 false);
            }

            if (file + 2 <= 7 && rank - 1 >= 0)
            {
                if (!is_occupied(board, file + 2, rank - 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file + 2,
                                                                 rank - 1),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 2, rank - 1, std::nullopt,
                                 false);
            }

            if (file + 1 <= 7 && rank - 2 >= 0)
            {
                if (!is_occupied(board, file + 1, rank - 2))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file + 1,
                                                                 rank - 2),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 1, rank - 2, std::nullopt,
                                 false);
            }

            if (file - 1 >= 0 && rank - 2 >= 0)
            {
                if (!is_occupied(board, file - 1, rank - 2))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file - 1,
                                                                 rank - 2),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 1, rank - 2, std::nullopt,
                                 false);
            }

            if (file - 2 >= 0 && rank - 1 >= 0)
            {
                if (!is_occupied(board, file - 2, rank - 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file - 2,
                                                                 rank - 1),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 2, rank - 1, std::nullopt,
                                 false);
            }

            if (file - 2 >= 0 && rank + 1 <= 7)
            {
                if (!is_occupied(board, file - 2, rank + 1))
                {
                    moves.emplace_back(src_boards[i], pos_to_int(file - 2,
                                                                 rank + 1),
                                       PieceType::KNIGHT, std::nullopt,
                                       std::nullopt, false, false, false,
                                       false);
                }

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 2, rank + 1, std::nullopt,
                                 false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_knight_captures(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(3 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            if (file - 1 >= 0 && rank + 2 <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 1, rank + 2, std::nullopt,
                                 false);
            }

            if (file + 1 <= 7 && rank + 2 <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 1, rank + 2, std::nullopt,
                                 false);
            }

            if (file + 2 <= 7 && rank + 1 <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 2, rank + 1, std::nullopt,
                                 false);
            }

            if (file + 2 <= 7 && rank - 1 >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 2, rank - 1, std::nullopt,
                                 false);
            }

            if (file + 1 <= 7 && rank - 2 >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file + 1, rank - 2, std::nullopt,
                                 false);
            }

            if (file - 1 >= 0 && rank - 2 >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 1, rank - 2, std::nullopt,
                                 false);
            }

            if (file - 2 >= 0 && rank - 1 >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 2, rank - 1, std::nullopt,
                                 false);
            }

            if (file - 2 >= 0 && rank + 1 <= 7)
            {

                add_capture_move(moves, src_boards[i], PieceType::KNIGHT,
                                 board, file - 2, rank + 1, std::nullopt,
                                 false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_queen_moves(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(0 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //UP
            int p = 1;
            while (rank + p <= 7 && !is_occupied(board, file, rank + p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file, rank + p),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file, rank + p, std::nullopt, false);
            }

            //UP + LEFT
            p = 1;
            while (file - p >= 0 && rank + p <= 7 &&
                   !is_occupied(board, file - p, rank + p))
            {
                moves.emplace_back(src_boards[i],
                                   pos_to_int(file - p, rank + p),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (file - p >= 0 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file - p, rank + p, std::nullopt,
                                 false);
            }

            //LEFT
            p = 1;
            while (file - p >= 0 && !is_occupied(board, file - p, rank))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file - p, rank),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (file - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file - p, rank, std::nullopt, false);
            }

            //DOWN + LEFT
            p = 1;
            while (file - p >= 0 && rank - p >= 0
                   && !is_occupied(board, file - p, rank - p))
            {
                moves.emplace_back(src_boards[i],
                                   pos_to_int(file - p, rank - p),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (file - p >= 0 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file - p, rank - p, std::nullopt,
                                 false);
            }

            //DOWN
            p = 1;
            while (rank - p >= 0 && !is_occupied(board, file, rank - p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file, rank - p),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file, rank - p, std::nullopt, false);
            }

            //DOWN + RIGHT
            p = 1;
            while (file + p <= 7 && rank - p >= 0
                   && !is_occupied(board, file + p, rank - p))
            {
                moves.emplace_back(src_boards[i],
                                   pos_to_int(file + p, rank - p),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (file + p <= 7 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file + p, rank - p, std::nullopt,
                                 false);
            }

            //RIGHT
            p = 1;
            while (file + p <= 7 && !is_occupied(board, file + p, rank))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file + p, rank),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (file + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file + p, rank, std::nullopt, false);
            }

            //UP + RIGHT
            p = 1;
            while (file + p <= 7 && rank + p <= 7
                   && !is_occupied(board, file + p, rank + p))
            {
                moves.emplace_back(src_boards[i],
                                   pos_to_int(file + p, rank + p),
                                   PieceType::QUEEN, std::nullopt,
                                   std::nullopt, false, false,
                                   false, false);
                p++;
            }
            if (file + p <= 7 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file + p, rank + p, std::nullopt,
                                 false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_queen_captures(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(0 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //UP
            int p = 1;
            while (rank + p <= 7 && !is_occupied(board, file, rank + p))
                p++;
            if (rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file, rank + p, std::nullopt, false);
            }

            //UP + LEFT
            p = 1;
            while (file - p >= 0 && rank + p <= 7 &&
                   !is_occupied(board, file - p, rank + p))
                p++;
            if (file - p >= 0 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file - p, rank + p, std::nullopt,
                                 false);
            }

            //LEFT
            p = 1;
            while (file - p >= 0 && !is_occupied(board, file - p, rank))
                p++;
            if (file - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file - p, rank, std::nullopt, false);
            }

            //DOWN + LEFT
            p = 1;
            while (file - p >= 0 && rank - p >= 0
                   && !is_occupied(board, file - p, rank - p))
                p++;
            if (file - p >= 0 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file - p, rank - p, std::nullopt,
                                 false);
            }

            //DOWN
            p = 1;
            while (rank - p >= 0 && !is_occupied(board, file, rank - p))
                p++;
            if (rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file, rank - p, std::nullopt, false);
            }

            //DOWN + RIGHT
            p = 1;
            while (file + p <= 7 && rank - p >= 0
                   && !is_occupied(board, file + p, rank - p))
                p++;
            if (file + p <= 7 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file + p, rank - p, std::nullopt,
                                 false);
            }

            //RIGHT
            p = 1;
            while (file + p <= 7 && !is_occupied(board, file + p, rank))
                p++;
            if (file + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file + p, rank, std::nullopt, false);
            }

            //UP + RIGHT
            p = 1;
            while (file + p <= 7 && rank + p <= 7
                   && !is_occupied(board, file + p, rank + p))
                p++;
            if (file + p <= 7 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::QUEEN,
                                 board, file + p, rank + p, std::nullopt,
                                 false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_bishop_moves(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(2 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //UP + LEFT
            int p = 1;
            while (file - p >= 0 && rank + p <= 7
                   && !is_occupied(board, file - p, rank + p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file - p,
                                                             rank + p),
                                   PieceType::BISHOP, std::nullopt,
                                   std::nullopt, false, false, false, false);
                p++;
            }
            if (file - p >= 0 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file - p, rank + p, std::nullopt,
                                 false);
            }

            //DOWN + LEFT
            p = 1;
            while (file - p >= 0 && rank - p >= 0
                   && !is_occupied(board, file - p, rank - p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file - p,
                                                             rank - p),
                                   PieceType::BISHOP, std::nullopt,
                                   std::nullopt, false, false, false, false);
                p++;
            }
            if (file - p >= 0 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file - p, rank - p, std::nullopt,
                                 false);
            }

            //DOWN + RIGHT
            p = 1;
            while (file + p <= 7 && rank - p >= 0
                   && !is_occupied(board, file + p, rank - p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file + p,
                                                             rank - p),
                                   PieceType::BISHOP, std::nullopt,
                                   std::nullopt, false, false, false, false);
                p++;
            }
            if (file + p <= 7 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file + p, rank - p, std::nullopt,
                                 false);
            }


            //UP + RIGHT
            p = 1;
            while (file + p <= 7 && rank + p <= 7
                   && !is_occupied(board, file + p, rank + p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file + p,
                                                             rank + p),
                                   PieceType::BISHOP, std::nullopt,
                                   std::nullopt, false, false, false, false);
                p++;
            }
            if (file + p <= 7 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file + p, rank + p, std::nullopt,
                                 false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_bishop_captures(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(2 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //UP + LEFT
            int p = 1;
            while (file - p >= 0 && rank + p <= 7
                   && !is_occupied(board, file - p, rank + p))
                p++;
            if (file - p >= 0 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file - p, rank + p, std::nullopt,
                                 false);
            }

            //DOWN + LEFT
            p = 1;
            while (file - p >= 0 && rank - p >= 0
                   && !is_occupied(board, file - p, rank - p))
                p++;
            if (file - p >= 0 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file - p, rank - p, std::nullopt,
                                 false);
            }

            //DOWN + RIGHT
            p = 1;
            while (file + p <= 7 && rank - p >= 0
                   && !is_occupied(board, file + p, rank - p))
                p++;
            if (file + p <= 7 && rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file + p, rank - p, std::nullopt,
                                 false);
            }


            //UP + RIGHT
            p = 1;
            while (file + p <= 7 && rank + p <= 7
                   && !is_occupied(board, file + p, rank + p))
                p++;
            if (file + p <= 7 && rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::BISHOP,
                                 board, file + p, rank + p, std::nullopt,
                                 false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_rook_moves(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(1 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //UP
            int p = 1;
            while (rank + p <= 7 && !is_occupied(board, file, rank + p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file, rank + p),
                                   PieceType::ROOK, std::nullopt, std::nullopt,
                                   false, false, false, false);
                p++;
            }
            if (rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file, rank + p, std::nullopt, false);
            }

            //LEFT
            p = 1;
            while (file - p >= 0 && !is_occupied(board, file - p, rank))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file - p, rank),
                                   PieceType::ROOK, std::nullopt, std::nullopt,
                                   false, false, false, false);
                p++;
            }
            if (file - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file - p, rank, std::nullopt, false);
            }

            //DOWN
            p = 1;
            while (rank - p >= 0 && !is_occupied(board, file, rank - p))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file, rank - p),
                                   PieceType::ROOK, std::nullopt, std::nullopt,
                                   false, false, false, false);
                p++;
            }
            if (rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file, rank - p, std::nullopt, false);
            }

            //RIGHT
            p = 1;
            while (file + p <= 7 && !is_occupied(board, file + p, rank))
            {
                moves.emplace_back(src_boards[i], pos_to_int(file + p, rank),
                                   PieceType::ROOK, std::nullopt, std::nullopt,
                                   false, false, false, false);
                p++;
            }
            if (file + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file + p, rank, std::nullopt, false);
            }
        }
        return moves;
    }

    std::vector<Move> Rule::generate_rook_captures(const Chessboard& board)
    {
        std::vector<Move> moves;

        std::vector<uint64_t> src_boards =
            board.rep_get().split_boards(1 + 6 * !(board.white_turn_get()));
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //UP
            int p = 1;
            while (rank + p <= 7 && !is_occupied(board, file, rank + p))
                p++;
            if (rank + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file, rank + p, std::nullopt, false);
            }

            //LEFT
            p = 1;
            while (file - p >= 0 && !is_occupied(board, file - p, rank))
                p++;
            if (file - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file - p, rank, std::nullopt, false);
            }

            //DOWN
            p = 1;
            while (rank - p >= 0 && !is_occupied(board, file, rank - p))
                p++;
            if (rank - p >= 0)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file, rank - p, std::nullopt, false);
            }

            //RIGHT
            p = 1;
            while (file + p <= 7 && !is_occupied(board, file + p, rank))
                p++;
            if (file + p <= 7)
            {
                add_capture_move(moves, src_boards[i], PieceType::ROOK,
                                 board, file + p, rank, std::nullopt, false);
            }
        }
        return moves;
    }

}
