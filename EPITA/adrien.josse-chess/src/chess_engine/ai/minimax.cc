#include <algorithm>

#include "ai.hh"
#include "logger.hh"
#include "minimax.hh"

#define SEARCH_DEPTH 3
#define CAPTURE_DEPTH 5
#define TIME_LIMIT 15000

namespace ai
{
    using ms_t = std::chrono::milliseconds;

    static inline bool timeout(ms_t end_time)
    {
        ms_t current_time = std::chrono::duration_cast<ms_t>(
            std::chrono::system_clock::now().time_since_epoch()
        );

        if (current_time >= end_time)
            return true;
        return false;
    }

    board::Move Minimax::search(board::Chessboard& board)
    {
        auto moves = board.generate_legal_moves();
        int alpha = -10000;
        int beta = 10000;
        int best_eval = 1234567890;
        board::Move best_move;

        ms_t start_time = std::chrono::duration_cast<ms_t>(
            std::chrono::system_clock::now().time_since_epoch()
        );
        auto end_time = start_time + std::chrono::milliseconds(TIME_LIMIT);
        int move_divider = moves.size();

        utils::Logger::starteval();
        for (auto move : moves)
        {
            if (timeout(end_time))
                break;

            ms_t current_time = std::chrono::duration_cast<ms_t>(
                std::chrono::system_clock::now().time_since_epoch()
            );
            ms_t remaining = end_time - current_time;
            auto move_time = ms_t(remaining / move_divider--);

            auto board_cp = board::Chessboard(board);
            board_cp.do_move(move, false);

            if (board.white_turn_get())
            {
                int res = min(board_cp, SEARCH_DEPTH - 1, alpha, beta,
                              current_time + move_time);
                //int res_eval = minMC(board_cp, depth - 1);
                if (res > alpha)
                {
                    alpha = res;
                    best_eval = res;
                    best_move = move;
                }
                //std::cout << "info score cp " << res
                //          << "time"
                //          << (current_time - start_time).count()
                //          << std::endl;
                utils::Logger::uci_output(std::string("info score cp ")
                + std::to_string(res) + " time "
                + std::to_string((current_time - start_time).count())
                + "ms");
            }
            else
            {
                int res = max(board_cp, SEARCH_DEPTH - 1, alpha, beta,
                              current_time + move_time);
                //int res_eval = maxMC(board_cp, depth - 1);
                if (res < beta)
                {
                    beta = res;
                    best_eval = res;
                    best_move = move;
                }
                //std::cout << "info score cp " << res
                //          << "time"
                //          << (current_time - start_time).count()
                //          << std::endl;
                utils::Logger::uci_output(std::string("info score cp ")
                + std::to_string(res) + " time "
                + std::to_string((current_time - start_time).count())
                + "ms");
            }
        }

        utils::Logger::endeval(best_eval);
        return best_move;
    }

    int Minimax::min(board::Chessboard& board, int depth, int alpha, int beta,
                     ms_t end_time)
    {
        if (depth == 0 || timeout(end_time))
            return -quiesce(board, -beta, -alpha, CAPTURE_DEPTH, end_time);

        std::vector<board::Move> moves;

        moves = board.generate_legal_moves();
        if (moves.empty())
            return AI::evaluate(board);
        if (board.is_draw())
            return 0;

        for (auto move : moves)
        {
            auto board_cp = board::Chessboard(board);
            board_cp.do_move(move, false);
            int res = max(board_cp, depth - 1, alpha, beta, end_time);

            if (res <= alpha)
                return alpha;
            if (res < beta)
                beta = res;
        }

        return beta;
    }

    int Minimax::max(board::Chessboard& board, int depth, int alpha, int beta,
                     ms_t end_time)
    {
        if (depth == 0 || timeout(end_time))
            return quiesce(board, alpha, beta, CAPTURE_DEPTH, end_time);

        std::vector<board::Move> moves;

        moves = board.generate_legal_moves();
        if (moves.empty())
            return AI::evaluate(board);
        if (board.is_draw())
            return 0;

        for (auto move : moves)
        {
            auto board_cp = board::Chessboard(board);
            board_cp.do_move(move, false);
            int res = min(board_cp, depth - 1, alpha, beta, end_time);

            if (res >= beta)
                return beta;
            if (res > alpha)
                alpha = res;
        }

        return alpha;
    }

    int Minimax::quiesce(board::Chessboard& board,
                         int alpha, int beta, int depth,
                         std::chrono::milliseconds end_time)
    {
    int stand_pat = AI::evaluate(board) * (board.white_turn_get() ? 1 : -1);
    if (depth == 0 || timeout(end_time))
        return stand_pat;
    if (stand_pat >= beta)
        return beta;
    if (alpha < stand_pat)
        alpha = stand_pat;

    for(auto capture : board.generate_legal_captures())
    {
        auto board_cp = board::Chessboard(board);
        board_cp.do_move(capture, false);
        int res = -quiesce(board_cp, -beta, -alpha, depth - 1, end_time);

        if( res >= beta )
            return beta;
        if( res > alpha )
           alpha = res;
    }
    return alpha;
}


    // First try at Monte Carlo implem

    static bool cmp_sup_pair_move_int(std::pair<board::Move, int> lhs,
                                  std::pair<board::Move, int> rhs)
    {
        return lhs.second > rhs.second;
    }

    static bool cmp_inf_pair_move_int(std::pair<board::Move, int> lhs,
                                  std::pair<board::Move, int> rhs)
    {
        return lhs.second < rhs.second;
    }

    int Minimax::maxMC(board::Chessboard& board, int depth)
    {
        if (depth == 0)
            return AI::evaluate(board);

        auto moves = board.generate_legal_moves();
        std::vector<std::pair<board::Move, int>> moves_eval;
        for (auto move : moves)
        {
            auto board_cp = board::Chessboard(board);
            board_cp.do_move(move, false);
            int eval = AI::evaluate(board_cp);
            moves_eval.push_back(std::make_pair(move, eval));
        }

        std::sort(moves_eval.begin(), moves_eval.end(), cmp_sup_pair_move_int);

        int best_eval = -900;
        for (size_t i = 0; i < moves_eval.size() / 2; ++i)
        {
            auto board_cp = board::Chessboard(board);
            board_cp.do_move(moves_eval[i].first, false);
            int res = minMC(board_cp, depth - 1);
            if (res > best_eval)
                best_eval = res;
        }
        return best_eval;
    }

    int Minimax::minMC(board::Chessboard& board, int depth)
    {
        if (depth == 0)
            return AI::evaluate(board);

        auto moves = board.generate_legal_moves();
        std::vector<std::pair<board::Move, int>> moves_eval;
        for (auto move : moves)
        {
            auto board_cp = board::Chessboard(board);
            board_cp.do_move(move, false);
            int eval = AI::evaluate(board_cp);
            moves_eval.push_back(std::make_pair(move, eval));
        }

        std::sort(moves_eval.begin(), moves_eval.end(), cmp_inf_pair_move_int);

        int best_eval = 900;
        for (size_t i = 0; i < moves_eval.size() / 2; ++i)
        {
            auto board_cp = board::Chessboard(board);
            board_cp.do_move(moves_eval[i].first, false);
            int res = maxMC(board_cp, depth - 1);
            if (res < best_eval)
                best_eval = res;
        }
        return best_eval;
    }
}
