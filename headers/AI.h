#ifndef AI_H
#define AI_H

#include <vector>
#include "AIMove.h"
#include "Piece.h"
#include "Board.h"


/**
 * @brief Instance of class for AI player. Searches for possible moves in a 
 * position, evaluates each and picks one of top moves.
 */
class AI {
    private:
        int maxPly;
        bool color;
        Board* gameBoard;


        /**
         * @brief Collects possible moves for a side at a given position
         *
         * @param side Side to play
         * @param gb Pointer to Board instance for board to find moves on
         *
         * @return All possible moves for a player at a given position
         */
        std::vector<std::pair<AIMove, double>> collectMoves(bool side, Board* gb);

        // värdera positionens netto för spelaren
        /**
         * @brief Sums up total piece value for inquiring side, negative
         * if other side has more piece values, positive if side has more
         *
         * @param gb The board to be evaluated
         * @param side Inquiring side
         *
         * @return Total value of pieces in view of querist.
         */
        double evaluatePosition(Board* gb, bool side);


        /**
         * @brief Minmax type of algorithm. Searches for position value of a
         * given depth. Uses recursion until depth is out, or checkmate found.
         * Is called with a starting move
         *
         * @param move The starting move, this move is to be done before finding
         * moves possible for other side after this.
         *
         * @param depth Depth/ply. Depth 0 evaluates position after the move 
         * is done.
         *
         * @param gb A gameboard of Board type with a position before move is
         * done.
         *
         * @param moveSide The player who is about to make the next move
         *
         * @param absoluteSide The player who absoluteley is asking for 
         * evaluation of future position
         *
         * @return The minmax value of current move
         */
        double searchBalance(AIMove move, const int& depth, Board* gb, bool moveSide, bool absoluteSide);

        /**
         * @brief Generates a random integer in range 0-max, used for
         * pseudo-randomly choose among similar valued moves
         *
         * @param max Maximum value of the random value
         *
         * @return A pseudo-random integer in range 0-max.
         */
        int randomInt(const int& max);

    public:
        /**
         * @brief Constructor creates an AI of a color, who has access to the
         * playing game board.
         *
         * @param _color Color of player, white == 1, black == 0.
         * @param _gameBoard
         */
        AI(bool _color, Board* _gameBoard);

        /**
         * @brief Collects all possible moves, evaluates them with minmax
         * type of algorithm, selects one of possible candidates moves and
         * returns the selected move.
         *
         * @return Move by AI to be played
         */
        AIMove pickMove();

        /**
         * @brief Set the depth of the AI
         *
         * @param _ply integer value of depth. Depth 0 is position value after
         * one move. Depth 1 is position value after opponents best follow up
         * move. And so on. Currently range 0-3 is reasonable values cause of
         * no pruning implemented. 4 is absolute max, but takes some time.
         */
        void setPly(const int& _ply) { maxPly = _ply;}
};

#endif
