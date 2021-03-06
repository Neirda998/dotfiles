#pragma once

#include <optional>

#include "color.hh"
#include "piece-type.hh"
#include "position.hh"
#include "report-type.hh"

namespace board
{
    /* The move symbolize a movement of a piece. Every turn should
     * correspond to one move. It contains every informations related
     * to the action */
    class PgnMove final
    {
    public:
        /* initialize it with PgnMove::opt_piece_t { [PieceType] } */
        using opt_piece_t = std::optional<PieceType>;

        PgnMove(const Position& start, const Position& end, PieceType piece,
                bool capture, ReportType report,
                const opt_piece_t& promotion = std::nullopt);

        /*! \brief Generate a castling given a color and a side */
        static PgnMove generate_castling(bool queen_side, Color color);

        inline const Position& start_get()
        {
            return start_;
        }

        inline const Position& end_get()
        {
            return end_;
        }

        inline const PieceType& piece_get()
        {
            return piece_;
        }

        inline const opt_piece_t& promotion_get()
        {
            return promotion_;
        }

        inline bool capture_get()
        {
            return capture_;
        }

        inline const ReportType& report_get()
        {
            return report_;
        }

        void report_set(ReportType report);


    private:
        // The original position of the piece
        const Position start_;

        // The destination of the piece
        const Position end_;

        // The type of the moving piece
        PieceType piece_;

        // if promotion, contains the piecetype generated by the promotion
        opt_piece_t promotion_;

        // if the move is a capture
        bool capture_;

        // type of report given by the pgn file
        ReportType report_;
    };
} // namespace board
