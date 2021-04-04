#include <map>

#include "chessboard-representation.hh"
#include "utils.hh"

namespace board
{

    static void set_color(std::vector<uint64_t>& bitboards, bool color)
    {
        // Starting ranks for each colors
        size_t start_rank = color ? 7 : 0;
        size_t pawn_rank = color ? 6 : 1;

        // Sets Queen to position D1
        bitboards[0 + color * 6] = pos_to_int(3, start_rank);

        bitboards[1 + color * 6] = pos_to_int(0, start_rank)
                                    + pos_to_int(7, start_rank);

        bitboards[2 + color * 6] = pos_to_int(2, start_rank)
                                    + pos_to_int(5, start_rank);

        bitboards[3 + color * 6] = pos_to_int(1, start_rank)
                                    + pos_to_int(6, start_rank);

        for (size_t i = 0; i <= 7; ++i)
            bitboards[4 + color * 6] += pos_to_int(i, pawn_rank);

        bitboards[5 + color * 6] = pos_to_int(4, start_rank);
    }

    ChessboardRepresentation::ChessboardRepresentation()
    {
        bitboards_ = std::vector<uint64_t>(12);

        set_color(bitboards_, 0);
        set_color(bitboards_, 1);
    }

    ChessboardRepresentation::ChessboardRepresentation
    (std::vector<std::tuple<size_t, size_t, size_t>> pieces)
    {
        bitboards_ = std::vector<uint64_t>(12);

        for (size_t i = 0; i < pieces.size(); ++i)
        {
            bitboards_[std::get<2>(pieces[i])]
                += pos_to_int(std::get<0>(pieces[i]), std::get<1>(pieces[i]));
        }
    }

    std::vector<uint64_t>
    ChessboardRepresentation::split_boards(int bit_idx) const
    {
        auto ret = std::vector<uint64_t>();
        uint64_t idx = 1;
        for (int i = 1; i <= 64; ++i)
        {
            if (bitboards_[bit_idx] & idx)
                ret.push_back(idx);
            idx = idx << 1;
        }
        return ret;
    }

    void ChessboardRepresentation::do_move(const Move& move, bool white,
                                           uint64_t en_passant)
    {
        int idx = static_cast<int>(move.piece_get()) + 6 * !white;

        bitboards_[idx] -= move.src_state_get();

        if (move.promotion_get())
            idx = static_cast<int>(move.promotion_get().value()) + 6 * !white;

        bitboards_[idx] += move.dst_state_get();

        if (move.capture_get())
        {
            idx = static_cast<size_t>(move.capture_get().value()) + 6 * white;
            if (move.en_passant_get())
                bitboards_[idx] -= en_passant;
            else
                bitboards_[idx] -= move.dst_state_get();
        }

        if (white && move.king_castling_get())
        {
            bitboards_[6 * !white + 1] -= 72057594037927936;
            bitboards_[6 * !white + 1] += 1099511627776;
        }
        if (white && move.queen_castling_get())
        {
            bitboards_[6 * !white + 1] -= 1;
            bitboards_[6 * !white + 1] += 16777216;
        }
        if (!white && move.king_castling_get())
        {
            uint64_t bignum = 134217728;
            bignum *= 68719476736;
            bitboards_[6 * !white + 1] -= bignum;
            bitboards_[6 * !white + 1] += 140737488355328;
        }
        if (!white && move.queen_castling_get())
        {
            bitboards_[6 * !white + 1] -= 128;
            bitboards_[6 * !white + 1] += 2147483648;
        }

    }

    std::string
    ChessboardRepresentation::generate_ascii_board(size_t bit_idx) const
    {
        const std::map<size_t, char> bit_idx_to_char =
        {
            {0, 'Q'}, {1, 'R'}, {2, 'B'}, {3, 'N'}, {4, 'P'}, {5, 'K'},
            {6, 'q'}, {7, 'r'}, {8, 'b'}, {9, 'n'}, {10, 'p'}, {11, 'k'}
        };

        std::vector<char> board;

        for (int i = 7; i >= 0; --i)
        {
            board.push_back('1' + i);
            board.push_back(' ');
            for (size_t j = 0; j < 8; ++j)
            {
                if (bit_idx < 12)
                {
                    if (bitboards_[bit_idx] & pos_to_int(j, i))
                        board.push_back(bit_idx_to_char.at(bit_idx));
                    else
                        board.push_back('.');
                }
                else
                {
                    size_t piece_idx = get_sqr_piece(j, i);

                    if (piece_idx == 12)
                        board.push_back('.');
                    else
                        board.push_back(bit_idx_to_char.at(piece_idx));
                }
                board.push_back(' ');
            }
            board.push_back('\n');
        }

        std::string board_str(board.begin(), board.end());
        board_str += "  A B C D E F G H \n";
        return board_str;
    }

    bool ChessboardRepresentation::operator==
        (const ChessboardRepresentation& rep) const
    {
        return bitboards_ == rep.bitboards_get();
    }
}
