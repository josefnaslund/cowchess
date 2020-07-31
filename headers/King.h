#ifndef KING_H
#define KING_H

#include "Board.h"
#include "Piece.h"

/**
 * @brief King inherits Piece and override movement rules etc. to give the king
 * his movements.
 */
class King : public Piece 
{
    public:
        /**
         * @brief Initializing constructor to give a new King his colour and
         * reference to board.
         *
         * @param color 1 for white, 0 for black
         * @param _gameBoard Pointer to it's board
         */
        King(bool color, Board* _gameBoard);

        /**
         * @brief General rules for king movement.
         *
         * @param oldX King column position
         * @param oldY King row position
         * @param newX The column query - can it move there?
         * @param newY The row query - can it move there?
         * @param b Piece pointer 2d array
         * @param testCheck Test for check when moving?
         *
         * @return True if valid move
         */
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief All surrounding squares of king are "controlled" by king.
         * This function tests if a square is that kind of square.
         *
         * @param oldX King column position
         * @param oldY King row position
         * @param newX The column query - can it move there?
         * @param newY The row query - can it move there?
         * @param b Piece pointer 2d array
         * @param testCheck Test for check when moving?
         *
         * @return True if adjacent
         */
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
};

#endif
