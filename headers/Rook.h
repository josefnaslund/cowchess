#ifndef ROOK_H
#define ROOK_H

#include "Board.h"
#include "Piece.h"


/**
 * @brief Rook piece, is inherited by queen.
 */
class Rook : public virtual Piece 
{
    public:

        /**
         * @brief Constructor initalizes a rook of a color with associated
         * board.
         *
         * @param color True for white, false for black.
         * @param _gameBoard "Board" rook resides on.
         */
        Rook(bool color, Board* _gameBoard);

        /**
         * @brief Query if piece can move to square. Calls rookValidMove(...)
         *
         * @param oldX Column position
         * @param oldY Row position
         * @param newX Column to move to
         * @param newY Row to move to
         * @param b 2d piece* array
         * @param testCheck Should we test check?
         *
         * @return True if valid
         */
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief Query if piece can move to square. Called by validMove(...)
         *
         * @param oldX Column position
         * @param oldY Row position
         * @param newX Column to move to
         * @param newY Row to move to
         * @param b 2d piece* array
         * @param testCheck Should we test check?
         *
         * @return True if valid
         */
        bool rookValidMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);

        /**
         * @brief Query if piece "controls" a square, including own pieces.
         * Calles rookControlsSquare(...)
         *
         * @param oldX Column position
         * @param oldY Row position
         * @param newX Column to move to
         * @param newY Row to move to
         * @param b 2d piece* array
         * @param testCheck Should we test check?
         *
         * @return True if valid
         */
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief Query if piece "controls" a square, including own pieces.
         * Called by controlsSquare(...)
         *
         * @param oldX Column position
         * @param oldY Row position
         * @param newX Column to move to
         * @param newY Row to move to
         * @param b 2d piece* array
         * @param testCheck Should we test check?
         *
         * @return True if valid
         */
        bool rookControlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);

        /**
         * @brief Returns value of rook
         *
         * @return value of rook
         */
        double getValue() override;
};

#endif
