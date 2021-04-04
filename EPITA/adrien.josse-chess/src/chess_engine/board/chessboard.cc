#include <tuple>
#include <stdexcept>

#include <iostream>

#include "chessboard.hh"
#include "logger.hh"
#include "rule.hh"
#include "utils.hh"

#define A1 1
#define A8 128
#define H1 (1ULL << 56)
#define H8 (1ULL << 63)

namespace board
{

    Chessboard::Chessboard()
        : white_turn_(true)
        , white_king_castling_(true)
        , white_queen_castling_(true)
        , black_king_castling_(true)
        , black_queen_castling_(true)
        , en_passant_(0)
        , white_threat_(-1)
        , black_threat_(-1)
        , is_three_repetitions_(false)
    {
        rep_ = ChessboardRepresentation();
        auto it = bitboard_history_.find(rep_);
        if (it != bitboard_history_.end())
            it->second++;
        else
            bitboard_history_.insert({rep_, 1});
    }

    static std::vector<std::pair<int, int>>
    get_coordinates_list(std::vector<uint64_t> board_list) {
        std::vector<std::pair<int, int>> empty;
        std::vector<std::pair<int, int>> res;
        for (uint64_t board : board_list) {
            if (get_coordinates(board).first == -1)
                return empty;
            res.push_back(get_coordinates(board));
        }
        return res;
    }

    Chessboard::Chessboard(const parsing::FenObject& fen_obj)
        : white_turn_(!static_cast<bool>(fen_obj.side_to_move_get()))
        , white_threat_(-1)
        , black_threat_(-1)
        , is_three_repetitions_(false)
    {
        auto pieces = std::vector<std::tuple<size_t, size_t, size_t>>();
        auto ranks = fen_obj.ranks_get();
        for (size_t i = 0; i < 8; ++i)
        {
            for (size_t j = 0; j < 8; ++j)
            {
                auto pos = static_cast<File>(j);
                auto piece = ranks[7 - i][pos];
                if (piece)
                {
                    size_t bit_idx = side_piece_to_bit_idx(piece.value());
                    pieces.push_back({j, i, bit_idx});
                }
            }
        }
        rep_ = ChessboardRepresentation(pieces);

        auto it = bitboard_history_.find(rep_);
        if (it != bitboard_history_.end())
            it->second++;
        else
            bitboard_history_.insert({rep_, 1});

        white_king_castling_ = false;
        white_queen_castling_ = false;
        black_king_castling_ = false;
        black_queen_castling_ = false;
        auto castling_opts = fen_obj.castling_get();
        if (castling_opts.size() != 1 or castling_opts[0] != '-')
        {
            for (auto& castling_opt : castling_opts)
            {
                switch (castling_opt)
                {
                case 'K':
                    white_king_castling_ = true;
                    break;
                case 'Q':
                    white_queen_castling_ = true;
                    break;
                case 'k':
                    black_king_castling_ = true;
                    break;
                case 'q':
                    black_queen_castling_ = true;
                    break;
                }
            }
        }

        if (fen_obj.en_passant_target_get() == std::nullopt)
            en_passant_ = 0;
        else
        {
            auto pos = fen_obj.en_passant_target_get().value();
            size_t file = static_cast<size_t>(pos.file_get());
            size_t rank = static_cast<size_t>(pos.rank_get());
            size_t rank_d = white_turn_ ? -1 : 1;
            en_passant_ = pos_to_int(file, rank + rank_d);
        }
    }

    void Chessboard::do_move(const Move& move, bool real_move)
    {
        rep_.do_move(move, white_turn_, en_passant_);

        auto it = bitboard_history_.find(rep_);
        if (it != bitboard_history_.end())
        {
            it->second++;
            if (it->second >= 3)
            {
                utils::Logger::repetitions(real_move, it->second);
                is_three_repetitions_ = true;
            }
        }
        else
            bitboard_history_.insert({rep_, 1});

        turn_++;

        auto piece = move.piece_get();
        auto dst_state = move.dst_state_get();
        auto capture = move.capture_get();
        if (capture != std::nullopt)
        {
            if (capture.value() == PieceType::ROOK)
            {
                white_queen_castling_ &= dst_state != A1;
                white_king_castling_ &= dst_state != H1;
                black_queen_castling_ &= dst_state != A8;
                black_king_castling_ &= dst_state != H8;
            }

            if (piece != PieceType::PAWN)
                draw_turn_++;
            else
                draw_turn_ = 0;
        }

        if ((white_king_castling_ || white_queen_castling_) && white_turn_)
        {
            auto src_state = move.src_state_get();
            if (piece == PieceType::ROOK)
            {
                white_queen_castling_ &= src_state != A1;
                white_king_castling_ &= src_state != H1;
            }
            else if (piece == PieceType::KING)
            {
                white_queen_castling_ = false;
                white_king_castling_ = false;
            }
        }
        else if ((black_queen_castling_ || black_king_castling_)
                 && !white_turn_)
        {
            auto src_state = move.src_state_get();
            if (piece == PieceType::ROOK)
            {
                black_queen_castling_ &= src_state != A8;

                black_king_castling_ &= src_state != H8;
            }
            else if (piece == PieceType::KING)
            {
                black_queen_castling_ = false;
                black_king_castling_ = false;
            }
        }

        if (move.double_pawn_push_get())
            en_passant_ = move.dst_state_get();
        else
            en_passant_ = 0;

        white_turn_ = !white_turn_;
        legal_moves_.clear();
        capture_moves_.clear();
        white_threat_ = -1;
        black_threat_ = -1;
    }

    bool Chessboard::is_move_legal(const Move& move)
    {
        auto chessboard_copy = Chessboard(*this);

        if (move.king_castling_get() or move.queen_castling_get())
        {
            if (get_threat(white_turn_))
                return false;
            auto board_cp = Chessboard(*this);
            if (move.king_castling_get())
            {
                auto mv = Move(move.src_state_get(),
                               move.src_state_get() * 256, PieceType::KING,
                               std::nullopt, std::nullopt,
                               false, false, false, false);
                board_cp.do_move(mv, false);
                if (board_cp.get_threat(!board_cp.white_turn_ != 0))
                    return false;
            }
            else
            {
                auto mv = Move(move.src_state_get(),
                               move.src_state_get() / 256, PieceType::KING,
                               std::nullopt, std::nullopt,
                               false, false, false, false);
                board_cp.do_move(mv, false);
                if (board_cp.get_threat(!board_cp.white_turn_ != 0))
                    return false;
            }
        }

        chessboard_copy.do_move(move, false);

        return chessboard_copy.get_threat(!chessboard_copy.white_turn_) == 0;
    }

    std::vector<Move> Chessboard::generate_legal_moves()
    {
        if (legal_moves_.empty())
        {
            std::vector<Move> pseudo_legal_moves;

            if (get_threat(white_turn_) >= 2)
                pseudo_legal_moves = Rule::generate_king_moves(*this);
            else
                pseudo_legal_moves = Rule::generate_all_moves(*this);

            for (auto move : pseudo_legal_moves)
            {
                if (is_move_legal(move))
                    legal_moves_.push_back(move);
            }
        }

        return legal_moves_;
    }

    std::vector<Move> Chessboard::generate_legal_captures()
    {
        if (capture_moves_.empty())
        {
            std::vector<Move> pseudo_legal_moves;

            if (get_threat(white_turn_) >= 2)
                pseudo_legal_moves = Rule::generate_king_captures(*this);
            else
                pseudo_legal_moves = Rule::generate_all_captures(*this);

            for (auto move : pseudo_legal_moves)
            {
                if (is_move_legal(move))
                    capture_moves_.push_back(move);
            }
        }

        return capture_moves_;
    }

    Move Chessboard::create_move(const Position& src, const Position& dst,
                                 const std::optional<PieceType>& promotion)
    {
        const size_t src_file = static_cast<size_t>(src.file_get());
        const size_t src_rank = static_cast<size_t>(src.rank_get());
        uint64_t src_bitboard = pos_to_int(src_file, src_rank);

        const size_t dst_file = static_cast<size_t>(dst.file_get());
        const size_t dst_rank = static_cast<size_t>(dst.rank_get());
        uint64_t dst_bitboard = pos_to_int(dst_file, dst_rank);

        auto move = Move(src_bitboard, dst_bitboard,
                         PieceType::QUEEN,
                         promotion, std::nullopt,
                         false, false, false, false);

        for (const auto& legal : generate_legal_moves())
        {
            if (move.src_state_get() == legal.src_state_get()
                && move.dst_state_get() == legal.dst_state_get()
                && move.promotion_get() == legal.promotion_get())
                return legal;
        }

        return Move();
    }

    bool Chessboard::is_draw()
    {
        //Three times
        if (is_three_repetitions_)
            return true;

        //50 turns (50 white turns + 50 black turns)
        if (draw_turn_ == 100)
            return true;

        //Stalemate
        if (is_stalemate())
            return true;

        return false;
    }

    Chessboard::opt_piece_t
    Chessboard::operator[](const Position& position) const
    {
        const size_t file = static_cast<size_t>(position.file_get());
        const size_t rank = static_cast<size_t>(position.rank_get());

        int piece_idx = rep_.get_sqr_piece(file, rank);
        if (piece_idx == 12)
            return std::nullopt;
        return std::make_pair<PieceType, Color>(
            static_cast<PieceType>(piece_idx % 6),
            static_cast<Color>(piece_idx / 6));
    }

    // PRIVATE METHODS
    int Chessboard::pawn_threat(bool white)
    {
        std::vector<uint64_t> src_boards =
            rep_get().split_boards(6 * white + 4);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);
        int rank_d = white ? -1 : 1;

        bool left_capt = false;
        bool right_capt = false;

        int res = 0;
        for (size_t i = 0; !(left_capt and right_capt)
                           and i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //Left capture
            if (!left_capt and file > 0)
            {
                int p = rep_.get_sqr_piece(file - 1, rank + rank_d);
                if (p == (6 * !white + 5))
                {
                    res++;
                    left_capt = true;
                    continue;
                }
            }

            //Right capture
            if (!right_capt and file < 7)
            {
                int p = rep_.get_sqr_piece(file + 1, rank + rank_d);
                if (p == (6 * !white + 5))
                {
                    res++;
                    right_capt = true;
                }
            }
        }
        return res;
    }

    int Chessboard::knight_threat(bool white)
    {
        std::vector<uint64_t> src_boards =
            rep_get().split_boards(6 * white + 3);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);
        int res = 0;
        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            if (file - 1 >= 0 && rank + 2 <= 7)
            {
                int p = rep_.get_sqr_piece(file - 1, rank + 2);
                if (p == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            if (file - 2 >= 0 && rank + 1 <= 7)
            {
                int p = rep_.get_sqr_piece(file - 2, rank + 1);
                if (p == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            if (file - 2 >= 0 && rank - 1 >= 0)
            {
                int p = rep_.get_sqr_piece(file - 2, rank - 1);
                if (p == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            if (file - 1 >= 0 && rank - 2 >= 0)
            {
                int p = rep_.get_sqr_piece(file - 1, rank - 2);
                if (p == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            if (file + 1 <= 7 && rank - 2 >= 0)
            {
                int p = rep_.get_sqr_piece(file + 1, rank - 2);
                if (p == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            if (file + 2 <= 7 && rank - 1 >= 0)
            {
                int p = rep_.get_sqr_piece(file + 2, rank - 1);
                if (p == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            if (file + 2 <= 7 && rank + 1 <= 7)
            {
                int p = rep_.get_sqr_piece(file + 2, rank + 1);
                if (p == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            if (file + 1 <= 7 && rank + 2 <= 7)
            {
                int p = rep_.get_sqr_piece(file + 1, rank + 2);
                if (p == (6 * !white + 5))
                    res++;
            }
        }
        return res;
    }

    int Chessboard::queen_threat(bool white)
    {
        std::vector<uint64_t> src_boards = rep_.split_boards(6 * white + 0);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);
        int res = 0;
        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;

            //UP
            int p = 1;
            while (rank + p <= 7 && !is_occupied(file, rank + p))
                p++;
            if (rank + p <= 7)
            {
                int q = rep_.get_sqr_piece(file, rank + p);
                if (q == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            //UP + LEFT
            p = 1;
            while (file - p >= 0 && rank + p <= 7
                    && !is_occupied(file - p, rank + p))
                p++;
            if (file - p >= 0 && rank + p <= 7)
            {
                int q = rep_.get_sqr_piece(file - p, rank + p);
                if (q == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            //LEFT
            p = 1;
            while (file - p >= 0 && !is_occupied(file - p, rank))
                p++;
            if (file - p >= 0)
            {
                int q = rep_.get_sqr_piece(file - p, rank);
                if (q == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            //DOWN + LEFT
            p = 1;
            while (file - p >= 0 && rank - p >= 0
                    && !is_occupied(file - p, rank - p))
                p++;
            if (file - p >= 0 && rank - p >= 0)
            {
                int q = rep_.get_sqr_piece(file - p, rank - p);
                if (q == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            //DOWN
            p = 1;
            while (rank - p >= 0 && !is_occupied(file, rank - p))
                p++;
            if (rank - p >= 0)
            {
                int q = rep_.get_sqr_piece(file, rank - p);
                if (q == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            //DOWN + RIGHT
            p = 1;
            while (file + p <= 7 && rank - p >= 0
                    && !is_occupied(file + p, rank - p))
                p++;
            if (file + p <= 7 && rank - p >= 0)
            {
                int q = rep_.get_sqr_piece(file + p, rank - p);
                if (q == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            //RIGHT
            p = 1;
            while (file + p <= 7 && !is_occupied(file + p, rank))
                p++;
            if (file + p <= 7)
            {
                int q = rep_.get_sqr_piece(file + p, rank);
                if (q == (6 * !white + 5))
                {
                    res++;
                    continue;
                }
            }

            //UP + RIGHT
            p = 1;
            while (file + p <= 7 && rank + p <= 7
                    && !is_occupied(file + p, rank + p))
                p++;
            if (file + p <= 7 && rank + p <= 7 )
            {
                int q = rep_.get_sqr_piece(file + p, rank + p);
                if (q == (6 * !white + 5))
                    res++;
            }

        }
        return res;
    }

    int Chessboard::rook_threat(bool white)
    {
        std::vector<uint64_t> src_boards = rep_.split_boards(6 * white + 1);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        bool up_capt = false;
        bool left_capt = false;
        bool down_capt = false;
        bool right_capt = false;

        int res = 0;
        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;
            int p;

            //UP
            if (!up_capt)
            {
                p = 1;
                while (rank + p <= 7 && !is_occupied(file, rank + p))
                    p++;
                if (rank + p <= 7)
                {
                    int q = rep_.get_sqr_piece(file, rank + p);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        up_capt = true;
                        continue;
                    }
                }
            }

            //LEFT
            if (!left_capt)
            {
                p = 1;
                while (file - p >= 0 && !is_occupied(file - p, rank))
                    p++;
                if (file - p >= 0)
                {
                    int q = rep_.get_sqr_piece(file - p, rank);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        left_capt = true;
                        continue;
                    }
                }
            }

            //DOWN
            if (!down_capt)
            {
                p = 1;
                while (rank - p >= 0 && !is_occupied(file, rank - p))
                    p++;
                if (rank - p >= 0)
                {
                    int q = rep_.get_sqr_piece(file, rank - p);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        down_capt = true;
                        continue;
                    }
                }
            }

            //RIGHT
            if (!right_capt)
            {
                p = 1;
                while (file + p <= 7 && !is_occupied(file + p, rank))
                    p++;
                if (file + p <= 7)
                {
                    int q = rep_.get_sqr_piece(file + p, rank);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        right_capt = true;
                    }
                }
            }
        }
        return res;
    }

    int Chessboard::bishop_threat(bool white)
    {
        std::vector<uint64_t> src_boards = rep_.split_boards(6 * white + 2);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        bool up_left_capt = false;
        bool down_left_capt = false;
        bool down_right_capt = false;
        bool up_right_capt = false;

        int res = 0;
        for (size_t i = 0; i < coords.size(); i++)
        {
            int file = coords[i].first;
            int rank = coords[i].second;
            int p = 1;

            //UP + LEFT
            if (!up_left_capt)
            {
                while (file - p >= 0 && rank + p <= 7
                        && !is_occupied(file - p, rank + p))
                    p++;
                if (file - p >= 0 && rank + p <= 7)
                {
                    int q = rep_.get_sqr_piece(file - p, rank + p);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        up_left_capt = true;
                        continue;
                    }
                }
            }

            //DOWN + LEFT
            p = 1;
            if (!down_left_capt)
            {
                while (file - p >= 0 && rank - p >= 0
                        && !is_occupied(file - p, rank - p))
                    p++;
                if (file - p >= 0 && rank - p >= 0)
                {
                    int q = rep_.get_sqr_piece(file - p, rank - p);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        down_left_capt = true;
                        continue;
                    }
                }
            }

            //DOWN + RIGHT
            p = 1;
            if (!down_right_capt)
            {
                while (file + p <= 7 && rank - p >= 0
                        && !is_occupied(file + p, rank - p))
                    p++;
                if (file + p <= 7 && rank - p >= 0)
                {
                    int q = rep_.get_sqr_piece(file + p, rank - p);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        down_right_capt = true;
                        continue;
                    }
                }
            }

            //UP + RIGHT
            p = 1;
            if (!up_right_capt)
            {
                while (file + p <= 7 && rank + p <= 7
                       && !is_occupied(file + p, rank + p))
                    p++;
                if (file + p <= 7 && rank + p <= 7 )
                {
                    int q = rep_.get_sqr_piece(file + p, rank + p);
                    if (q == (6 * !white + 5))
                    {
                        res++;
                        up_right_capt = true;
                    }
                }
            }

        }
        return res;
    }

    int Chessboard::king_threat(bool white)
    {
        std::vector<uint64_t> src_boards =
            rep_get().split_boards(6 * white + 5);
        std::vector<std::pair<int, int>> coords =
            get_coordinates_list(src_boards);

        if (coords.size() == 0)
            return 0;

        if (coords.size() > 1)
            throw std::logic_error("Why do I have multiple kings ?");

        int file = coords[0].first;
        int rank = coords[0].second;

        // UP + LEFT
        if (file > 0 && rank < 7)
        {
            int p = rep_.get_sqr_piece(file - 1, rank + 1);
            if (p == (6 * !white + 5))
                return 1;
        }

        // LEFT
        if (file > 0)
        {
            int p = rep_.get_sqr_piece(file - 1, rank);
            if (p == (6 * !white + 5))
                return 1;
        }

        // DOWN + LEFT
        if (file > 0 && rank > 0)
        {
            int p = rep_.get_sqr_piece(file - 1, rank - 1);
            if (p == (6 * !white + 5))
                return 1;
        }

        // DOWN
        if (rank > 0)
        {
            int p = rep_.get_sqr_piece(file, rank - 1);
            if (p == (6 * !white + 5))
                return 1;
        }

        // DOWN + RIGHT
        if (file < 7 && rank > 0)
        {
            int p = rep_.get_sqr_piece(file + 1, rank - 1);
            if (p == (6 * !white + 5))
                return 1;
        }

        // RIGHT
        if (file < 7)
        {
            int p = rep_.get_sqr_piece(file + 1, rank);
            if (p == (6 * !white + 5))
                return 1;
        }

        // UP + RIGHT
        if (file < 7 && rank < 7)
        {
            int p = rep_.get_sqr_piece(file + 1, rank + 1);
            if (p == (6 * !white + 5))
                return 1;
        }

        // UP
        if (rank < 7)
        {
            int p = rep_.get_sqr_piece(file, rank + 1);
            if (p == (6 * !white + 5))
                return 1;
        }

        return 0;
    }

    int Chessboard::get_threat(bool white)
    {
        if (white)
        {
            if (white_threat_ == -1)
            {
                white_threat_ = pawn_threat(white)
                + knight_threat(white)
                + queen_threat(white)
                + rook_threat(white)
                + bishop_threat(white)
                + king_threat(white);
            }
            return white_threat_;
        }
        else
        {
            if (black_threat_ == -1)
            {
                black_threat_ = pawn_threat(white)
                + knight_threat(white)
                + queen_threat(white)
                + rook_threat(white)
                + bishop_threat(white)
                + king_threat(white);
            }
            return black_threat_;
        }
    }
}
