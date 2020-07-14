#ifndef KNIGHT_H
#define KNIGHT_H

#include "Board.h"
#include "Piece.h"

class Knight : public Piece 
{
    public:
        Knight(bool color, Board* _gameBoard);
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
        bool controlsSquare(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck) override;
};

#endif
