#ifndef BISHOP_H
#define BISHOP_H

#include "Board.h"
#include "Piece.h"


/**
 * @brief Bishop piece. Contains piece info and rules for movement. Bishop (and
 * rook) has their validMove() and controlsSquare() call separate member
 * functions because of queen inherits Bishop and Rook.
 */
class Bishop : public virtual Piece 
{
    public:
        /**
         * @brief Construct bishop with info about colour/color and pointer
         * to Board object.
         *
         * @param color White is 1, black is 0.
         * @param _gameBoard Pointer to the board the piece is residing on.
         * So that it can find out where it can move.
         */
        Bishop(bool color, Board* _gameBoard);

        /**
         * @brief Query if a piece can legally move to a position. The bishop
         * validMove will call bishopValidMove(...)
         *
         * @param oldX The "moving from"-column
         * @param oldY The "moving from"-row
         * @param newX The "moving to"-column
         * @param newY The "moving to"-row
         * @param b Piece array to test on
         * @param testCheck Should it test for check on own side?
         *
         * @return true if piece can make that move
         */
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;


        /**
         * @brief Called by member validMove of bishop (and queen through
         * inheritance). Contains bishop rules.
         *
         * @param oldX The "moving from"-column
         * @param oldY The "moving from"-row
         * @param newX The "moving to"-column
         * @param newY The "moving to"-row
         * @param b Piece array to test on
         * @param testCheck Should it test for check on own side?
         *
         *
         * @return true if piece can make that move
         */
        bool bishopValidMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);

        /**
         * @brief Similar to validMove but also includes pieces of own colour
         * that is in piece movement reach. Calls bishopControlsSquare(...)
         *
         * @param oldX The "moving from"-column
         * @param oldY The "moving from"-row
         * @param newX The "moving to"-column
         * @param newY The "moving to"-row
         * @param b Piece array to test on
         * @param testCheck Should it test for check on own side?
         *
         *
         * @return true if square is within piece reach.
         */
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        /**
         * @brief Similar to bishopValidMove but also includes pieces of own colour
         * that is in piece movement reach. Called by controlsSquare(...)
         * (and by queen controlsSqquare(...))
         *
         * @param oldX The "moving from"-column
         * @param oldY The "moving from"-row
         * @param newX The "moving to"-column
         * @param newY The "moving to"-row
         * @param b Piece array to test on
         * @param testCheck Should it test for check on own side?
         *
         *
         * @return true if square is within piece reach.
         */
        bool bishopControlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);
};

#endif
