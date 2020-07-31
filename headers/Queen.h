#ifndef QUEEN_H
#define QUEEN_H

#include "Board.h"
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"

/**
 * @brief Queen uses multiple inheritance (diamond shaped) to get her rules.
 * Since a valid queen move is either a valid Rook move or a valid Bishop move.
 */
class Queen : public Rook, public Bishop
{
    private:
        // selecting wich 'alive' to use, since Queen has two (one from
        // Bishop too).
        using Rook::alive;

    public:
        /**
         * @brief Construct a queen of a color for a given board
         *
         * @param color true if white, false is black
         * @param _gameBoard Board she resides on.
         */
        Queen(bool color, Board* _gameBoard);

        /**
         * @brief Query if a move is possible
         *
         * @param oldX Column position queen resides on
         * @param oldY Row position queen resides on
         * @param newX Suggested column to move to
         * @param newY Suggested row to move to
         * @param b A 2d piece board representation
         * @param testCheck Should we test for check?
         *
         * @return true if valid
         */
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief Query if piece is guarding a square.
         *
         * @param oldX Column position queen resides on
         * @param oldY Row position queen resides on
         * @param newX Suggested square column to test
         * @param newY Suggested square row to test
         * @param b A 2d piece board representation
         * @param testCheck Should we test for check?
         *
         * @return true if valid
         */
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
};

#endif
