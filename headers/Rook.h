#ifndef ROOK_H
#define ROOK_H

#include "Board.h"
#include "Piece.h"


class Rook : virtual public Piece 
{
    public:
        Rook() {};
        Rook(bool color, Board* _gameBoard);
        virtual bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        bool rookValidMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);

        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        bool rookControlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);
};

#endif
