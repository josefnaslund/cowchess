#ifndef BISHOP_H
#define BISHOP_H

#include "Board.h"
#include "Piece.h"


class Bishop : virtual public Piece 
{
    public:
        Bishop() {};
        Bishop(bool color, Board* _gameBoard);
        virtual bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        bool bishopValidMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);

        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;

        bool bishopControlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck);
};

#endif
