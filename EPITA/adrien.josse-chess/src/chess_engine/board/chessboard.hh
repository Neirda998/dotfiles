#pragma once

#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "chessboard-interface.hh"
#include "chessboard-representation.hh"
#include "color.hh"
#include "fen_object.hh"
#include "move.hh"
#include "piece-type.hh"
#include "utils.hh"

namespace board {
    class Chessboard : public ChessboardInterface
    {
    public:
        using side_piece_t = std::pair<PieceType, Color>;
        using opt_piece_t = std::optional<side_piece_t>;

        Chessboard();

        Chessboard(ChessboardRepresentation rep, bool white_turn,
                    bool white_king_castling, bool white_queen_castling,
                    bool black_king_castling, bool black_queen_castling,
                    size_t turn)
                : rep_(rep)
                , white_turn_(white_turn)
                , white_king_castling_(white_king_castling)
                , white_queen_castling_(white_queen_castling)
                , black_king_castling_(black_king_castling)
                , black_queen_castling_(black_queen_castling)
                , turn_(turn)
                , white_threat_(-1)
                , black_threat_(-1)
                , is_three_repetitions_(false)
                {}

        Chessboard(const Chessboard& chessboard) = default;

        Chessboard(const parsing::FenObject& fen_obj);

        /* Getters */

        inline ChessboardRepresentation rep_get() const
        {
            return rep_;
        }

        inline bool white_turn_get() const
        {
            return white_turn_;
        }

        inline bool white_king_castling_get() const
        {
            return white_king_castling_;
        }

        inline bool white_queen_castling_get() const
        {
            return white_queen_castling_;
        }

        inline bool black_king_castling_get() const
        {
            return black_king_castling_;
        }

        inline bool black_queen_castling_get() const
        {
            return black_queen_castling_;
        }

        inline uint64_t en_passant_get() const
        {
            return en_passant_;
        }

        constexpr size_t turn_get()
        {
            return turn_;
        }

        inline std::string uci_last_get() const
        {
            return uci_last_;
        }

        // SETTER

        inline void en_passant_set(uint64_t pos)
        {
            en_passant_ = pos;
        }

        inline void uci_last_set(const std::string& uci_last)
        {
            uci_last_ = uci_last;
        }

        // Moves methods
        void do_move(const Move& move, bool real_move);

        bool is_move_legal(const Move& move);

        std::vector<Move> generate_legal_moves();
        std::vector<Move> generate_legal_captures();

        Move create_move(const Position& src, const Position& dst,
                         const std::optional<PieceType>& promotion);

        // Game state methods
        constexpr bool is_occupied(int file, int rank)
        {
            return rep_.get_sqr_piece(file, rank) != 12;
        }

        inline bool is_check()
        {
            return get_threat(white_turn_);
        }

        inline bool is_checkmate()
        {
            return is_check() && generate_legal_moves().size() == 0;
        }

        inline bool is_stalemate()
        {
            return !is_check() && generate_legal_moves().size() == 0;
        }

        bool is_draw();

        opt_piece_t operator[](const Position& position) const;

        // Threat methods
        int pawn_threat(bool white);
        int knight_threat(bool white);
        int queen_threat(bool white);
        int rook_threat(bool white);
        int bishop_threat(bool white);
        int king_threat(bool white);

        int get_threat(bool white);

    private:

        ChessboardRepresentation rep_;

        bool white_turn_;

        // if false, then castling is not forbidden
        bool white_king_castling_;

        bool white_queen_castling_;

        bool black_king_castling_;

        bool black_queen_castling_;

        // Bitboard slice representing the position of the last
        // double pawn pushed from the last turn. It is equal to
        // 0 if there is none.
        uint64_t en_passant_;

        size_t turn_;

        size_t draw_turn_;

        // Never use this call generate_moves method.
        std::vector<Move> legal_moves_;
        std::vector<Move> capture_moves_;

        // Never use this call get_threat method.
        int white_threat_;
        int black_threat_;

        // The following boolean is set to true whenver there is an
        // increment in bitboard_history that reaches three.
        bool is_three_repetitions_;
        std::unordered_map<ChessboardRepresentation, int, BitboardHash>
        bitboard_history_;

        // uci_history
        std::string uci_last_;
    };
}
