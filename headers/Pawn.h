#ifndef PAWN_H
#define PAWN_H

#include "Board.h"
#include "Piece.h"

/**
 * @brief Pawn piece. Contains info about the piece and its rules for movement.
 */
class Pawn : public Piece 
{
    public:
        /**
         * @brief Initialize a pawn with color and a Board.
         *
         * @param color White == 1, black == 0
         * @param _gameBoard Board pawn is on
         */
        Pawn(bool color, Board* _gameBoard);

        /**
         * @brief Check if a move is valid
         *
         * @param oldX Pawn "moving from" column position
         * @param oldY Pawn "moving from" row position
         * @param newX Pawn "moving to" column position
         * @param newY Pawn "moving to" row position
         * @param b 2d Piece pointer array
         * @param testCheck Should it test for check?
         *
         * @return true if valid move
         */
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief Check if a pawn controls a square (including own pieces)
         *
         * @param oldX Pawn column position
         * @param oldY Pawn row position
         * @param newX Pawn "moving to" column position
         * @param newY Pawn "moving to" row position
         * @param b 2d Piece pointer array
         * @param testCheck Should it test for check?
         *
         * @return true if valid move
         */
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;


        /**
         * @brief Get value of pawn
         *
         * @return Value of current pawn. Central pawns controlling central
         * squares are valued more than default.
         */
        double getValue() override;
};

#endif
