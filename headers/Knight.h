#ifndef KNIGHT_H
#define KNIGHT_H

#include "Board.h"
#include "Piece.h"

/**
 * @brief Contains rules for Knith piece. Inherits Piece and overrides movement.
 */
class Knight : public Piece 
{
    public:
        /**
         * @brief Initializing constuctor
         *
         * @param color Colour (1, white or 0, black).
         * @param _gameBoard Pointer to Board object knight resides on
         */
        Knight(bool color, Board* _gameBoard);

        /**
         * @brief Query if a move is possible
         *
         * @param oldX Old position column
         * @param oldY Old position row
         * @param newX New position column
         * @param newY New position row.
         * @param b 2d piece pointer array, where all pieces are at.
         * @param testCheck Should it test check?
         *
         * @return  True if move is valid. Contains rules for knight.
         */
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief Similar to validMove, but also tests if piece is guarding
         * own piece.
         *
         * @param oldX Old position column
         * @param oldY Old position row
         * @param newX New position column
         * @param newY New position row.
         * @param b 2d piece pointer array, where all pieces are at.
         * @param testCheck Should it test check?
         *
         * @return  True if square is within reach for piece.
         */
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief Get value of piece
         *
         * @return Piece value
         */
        double getValue() override;
};




#endif
